using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Diagnostics;
using UnrealModLauncher.Utilities;
using Microsoft.Win32;
using System.Runtime.Serialization;
using System.Collections.ObjectModel;
using System.IO;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Interop;

namespace UnrealModLauncher
{
    [DataContract]
    public class GameInfoList
    {
        [DataMember]
        public List<GameInfo> Games { get; set; }
    }

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public static readonly string _applicationDataPath = System.AppDomain.CurrentDomain.BaseDirectory;
        private static readonly ObservableCollection<GameInfo> _games = new ObservableCollection<GameInfo>();
        private readonly string gamesListPath;
        public static ReadOnlyObservableCollection<GameInfo> Games;
        public MainWindow()
        {
            InitializeComponent();

            try
            {
                //if (!Directory.Exists(_applicationDataPath)) Directory.CreateDirectory(_applicationDataPath);
                gamesListPath = $@"{_applicationDataPath}GameList.xml";
                Games = new ReadOnlyObservableCollection<GameInfo>(_games);


                if (File.Exists(gamesListPath))
                {
                    var games = Serializer.FromFile<GameInfoList>(gamesListPath).Games;
                    _games.Clear();
                    foreach (var game in games)
                    {
                        AddGameProfileToList(game);
                    }
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
                // TODO: Make Error Worky
            }
        }

        void button_Click(object sender, RoutedEventArgs e)
        {
            Button CurrentButton = (sender as Button);
            GameInfo Game = _games[(int)CurrentButton.Tag];
            Process GameProcess = ProcessManager.StartProcess(Game.GamePath, Game.Arguments);
            string ModLoaderPath = $@"{_applicationDataPath}UnrealModLoader.dll";
            ProcessManager.InjectDll(GameProcess, ModLoaderPath);
        }

        //If you get 'dllimport unknown'-, then add 'using System.Runtime.InteropServices;'
        [DllImport("gdi32.dll", EntryPoint = "DeleteObject")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool DeleteObject([In] IntPtr hObject);

        public ImageSource ImageSourceFromBitmap(Bitmap bmp)
        {
            var handle = bmp.GetHbitmap();
            try
            {
                return Imaging.CreateBitmapSourceFromHBitmap(handle, IntPtr.Zero, Int32Rect.Empty, BitmapSizeOptions.FromEmptyOptions());
            }
            finally { DeleteObject(handle); }
        }

        private void AddGameProfileToList(GameInfo game)
        {
            Icon icon = System.Drawing.Icon.ExtractAssociatedIcon(game.GamePath);
            var img = ImageSourceFromBitmap(icon.ToBitmap());

            Button button = new Button();
            button.HorizontalContentAlignment = HorizontalAlignment.Left;

            StackPanel GameInfoBox = new StackPanel
            {
                Orientation = Orientation.Horizontal
            };

            button.Content = GameInfoBox;

            var GameInfoImage = new System.Windows.Controls.Image
            {
                Source = img,
                Height = 50,
                Width = 50
            };

            var spacer1 = new Separator()
            {
                Width = 10,
                Background = new SolidColorBrush(Colors.Transparent)
            };

            var LableTest = new Label
            {
                Content = string.Format(game.GameName),
                VerticalAlignment = VerticalAlignment.Center
            };

            GameInfoBox.Children.Add(GameInfoImage);
            GameInfoBox.Children.Add(spacer1);
            GameInfoBox.Children.Add(LableTest);

            button.Tag = _games.Count;
            button.Click += new RoutedEventHandler(button_Click);

            this.GameSelectionPanel.Children.Add(button);

            _games.Add(game);
        }

        private void AddGame(object sender, RoutedEventArgs e)
        {
            OpenFileDialog selectExecutableDiaglog = new OpenFileDialog();
            selectExecutableDiaglog.Title = "Select Game Executable";
            selectExecutableDiaglog.Filter = "Game Executable (*.exe)|*.exe";
            selectExecutableDiaglog.ShowDialog();
            if(selectExecutableDiaglog.FileName != "")
            {
                string SelectedExecutable = selectExecutableDiaglog.FileName;

                GameInfo SelectedGame = new GameInfo();

                var gameNamestr = System.IO.Path.GetFileName(SelectedExecutable);
                gameNamestr = gameNamestr.Substring(0, gameNamestr.Length - 4);

                SelectedGame.GameName = gameNamestr;
                SelectedGame.GamePath = SelectedExecutable;

                GameDetailsWindow gameDetails = new GameDetailsWindow(SelectedGame);
                gameDetails.ShowDialog();

                AddGameProfileToList(SelectedGame);

                var games = _games.ToList();
                
                Serializer.ToFile(new GameInfoList() { Games = games }, gamesListPath);
            }
        }

        //private void Button_Click(object sender, RoutedEventArgs e)
        //{
        //    Process GameProcess = ProcessManager.StartProcess("E:\\Games\\SteamLibary\\steamapps\\common\\UNDEFEATED\\UNDEFEATED\\Binaries\\Win64\\UNDEFEATED-Win64-Shipping.exe");
        //    ProcessManager.InjectDll(GameProcess, "C:\\Users\\rcjer\\Documents\\GitHub\\UnrealModLoader\\x64\\Debug\\UnrealModLoader.dll");

        //}
    }
}
