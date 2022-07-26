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
using System.Windows.Shapes;

namespace UnrealModLauncher
{
    /// <summary>
    /// Interaction logic for GameDetailsWindow.xaml
    /// </summary>
    public partial class GameDetailsWindow : Window
    {
        private GameInfo gameInfo;
        public GameDetailsWindow(object game)
        {
            InitializeComponent();
            gameInfo = (GameInfo)game;
            GameShortName.Text = gameInfo.GameName;
            GamePath.Text = gameInfo.GamePath;
            Arguments.Text = gameInfo.Arguments;
            bAutoInject.IsChecked = gameInfo.AutoInject;
        }

        private void ApplyChanges(object sender, RoutedEventArgs e)
        {
            gameInfo.GameName = GameShortName.Text;
            gameInfo.GamePath = GamePath.Text;
            gameInfo.Arguments = Arguments.Text;
            gameInfo.AutoInject = (bool)bAutoInject.IsChecked;

            Close();
        }

        private void ExitDetails(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
