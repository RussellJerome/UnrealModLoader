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
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Newtonsoft.Json;
using UnrealModLauncher.Utilities.Commands;

namespace UnrealModLauncher
{
    public class BaseModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged([CallerMemberName] string name = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
    }

    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            DataContext = new MainWindowModel(this);
        }

        public class MainWindowModel : BaseModel
        {
            private MainWindow _view;

            private string documentPath = System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), "UnrealModLauncher");

            #region Commands
            public IAsyncCommand AddGameCommand { get; private set; }
            public IAsyncCommand<GameInfo> RemoveGameCommand { get; private set; }
            public IAsyncCommand<GameInfo> EditGameCommand { get; private set; }
            public IAsyncCommand<GameInfo> LaunchGameCommand { get; private set; }
            #endregion

            private ObservableCollection<GameInfo> _gameList;
            public ObservableCollection<GameInfo> GameList
            {
                get { return _gameList; }
                set
                {
                    _gameList = value;
                    OnPropertyChanged("GameList");
                }
            }


            public MainWindowModel(MainWindow view)
            {
                _view = view;

                AddGameCommand = new AsyncCommand(AddGame);
                RemoveGameCommand = new AsyncCommand<GameInfo>(RemoveGame);
                EditGameCommand = new AsyncCommand<GameInfo>(EditGame);
                LaunchGameCommand = new AsyncCommand<GameInfo>(LaunchGame);

                GameList = new ObservableCollection<GameInfo>();

                Task.Run(async () =>
                {
                    await Refresh();
                }).ConfigureAwait(false);
            }

            public async Task Refresh()
            {
                await LoadGames();
            }

            private async Task LoadGames()
            {
                if (!Directory.Exists(documentPath))
                {
                    Directory.CreateDirectory(documentPath);

                    return;
                }

                if (!File.Exists(System.IO.Path.Combine(documentPath, "games.json")))
                {
                    return;
                }

                using (StreamReader sr = new StreamReader(System.IO.Path.Combine(documentPath, "games.json")))
                {
                    GameList = new ObservableCollection<GameInfo>(
                        JsonConvert.DeserializeObject<IEnumerable<GameInfo>>(
                            await sr.ReadToEndAsync()
                        )
                    );

                    OnPropertyChanged("GameList");
                }
            }

            private async Task SaveGames()
            {
                using (StreamWriter sw = new StreamWriter(System.IO.Path.Combine(documentPath, "games.json")))
                {
                    await sw.WriteAsync(JsonConvert.SerializeObject(GameList));
                }
            }

            private async Task AddGame()
            {
                OpenFileDialog fileDlg = new OpenFileDialog();
                fileDlg.Title = "Select Game Executable";
                fileDlg.Filter = "Game Executable (*.exe)|*.exe";
                
                if (fileDlg.ShowDialog() == true)
                {
                    if (!string.IsNullOrEmpty(fileDlg.FileName))
                    {
                        GameInfo gameInfo = GameInfo.Create();
                        gameInfo.GameName = System.IO.Path.GetFileName(fileDlg.FileName).Replace(".exe", "");
                        gameInfo.GamePath = fileDlg.FileName;

                        GameDetailsWindow gameDetailsDlg = new GameDetailsWindow(gameInfo);

                        if (gameDetailsDlg.ShowDialog() == true)
                        {
                            GameList.Add(gameInfo);

                            await SaveGames();
                        }
                    }
                }
            }

            private async Task RemoveGame(GameInfo gameInfo)
            {
                GameList.Remove(gameInfo);

                await SaveGames();
            }

            private async Task EditGame(GameInfo gameInfo)
            {
                GameDetailsWindow gameDetailsDlg = new GameDetailsWindow(gameInfo);

                if (gameDetailsDlg.ShowDialog() == true)
                {
                    await SaveGames();

                    GameList = new ObservableCollection<GameInfo>(GameList);
                }
            }

            private async Task LaunchGame(GameInfo gameInfo)
            {
                await Task.Run(() =>
                {
                    Process GameProcess = ProcessManager.StartProcess(gameInfo.GamePath, gameInfo.Arguments);
                    string ModLoaderPath = System.IO.Path.Combine(System.AppDomain.CurrentDomain.BaseDirectory, "UnrealModLoader.dll");
                    ProcessManager.InjectDll(GameProcess, ModLoaderPath);
                });
            }
        }
    }
}