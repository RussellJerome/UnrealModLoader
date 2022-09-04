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
        private GameInfo GameInfo;
        public GameDetailsWindow(GameInfo gameInfo)
        {
            InitializeComponent();
            GameInfo = gameInfo;

            GameShortName.Text = gameInfo.GameName;
            GamePath.Text = gameInfo.GamePath;
            Arguments.Text = gameInfo.Arguments;
        }

        private void ApplyChanges(object sender, RoutedEventArgs e)
        {
            GameInfo.GameName = GameShortName.Text;
            GameInfo.GamePath = GamePath.Text;
            GameInfo.Arguments = Arguments.Text;

            DialogResult = true;
            Close();
        }

        private void ExitDetails(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
