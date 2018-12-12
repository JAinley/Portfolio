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

using System.IO;    // library used for file handling


namespace MIG13_Practical04
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    /// 

    public partial class MainWindow : Window
    {
        Image spriteSelected;
        public MainWindow()
        {
            InitializeComponent();
            spriteSelected = new Image();


        }

        /// <summary>
        /// Basic function definition
        /// </summary>
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
        }


        Image i = new Image();
        BitmapImage src = new BitmapImage();

        /// <summary>
        /// Create a TextBox programmatically
        /// </summary>
        private void createMyTxtBox()
        {
            // instantiate the TextBox object
            TextBox tbx_myDisplay02 = new TextBox();

            // specify some of the parameters/features
            tbx_myDisplay02.Height = 148;
            tbx_myDisplay02.Width = 300;
            tbx_myDisplay02.Text = "Josh";

            // add to the Grid control
            myGrid.Children.Add(tbx_myDisplay02);
        }

        #region FILE-HANDLING
        /// <summary>
        /// Write to a txt file
        /// </summary>


        /// <summary>
        /// Read data from a text file
        /// </summary>

        #endregion

        #region INTERACTION
        private void btn_Write_Click(object sender, RoutedEventArgs e)
        {

        }

        private void btn_Read_Click(object sender, RoutedEventArgs e)
        {

        }


        private void txtbx_Clear(object sender, RoutedEventArgs e)
        {

        }
        #endregion

        private void btn_Load_Map(object sender, RoutedEventArgs e)
        {
            Console.WriteLine("ok");
            Image i = new Image();
            BitmapImage src = new BitmapImage();
            //src.BeginInit();
            Canvas1.Background = Brushes.Green;
            //src.UriSource = new Uri(@"U:\Year 2 semester 1\multimodal interface work\MIG13_Practical04\MIG13_Practical04\tile.png", UriKind.Absolute);
            //src.CacheOption = BitmapCacheOption.OnLoad;
            //src.EndInit();
            i.Source = src;
            i.Stretch = Stretch.Uniform;
            //int q = src.PixelHeight;        // Image loads here
            Canvas1.Children.Add(i);
        }
        private void btn_Load_MapD(object sender, RoutedEventArgs e)
        {
 
            Console.WriteLine("ok");
            Image i = new Image();
            BitmapImage src = new BitmapImage();
            i.Width = 1000;
            i.Height = 481;
        
            Canvas1.Background = Brushes.SandyBrown;
 
            i.Source = src;
            i.Stretch = Stretch.UniformToFill;
           // int q = src.PixelHeight;        // Image loads here
            Canvas1.Children.Add(i);
        }

        private void btn_Tile_Map(object sender, RoutedEventArgs e)
        {

            Console.WriteLine("ok");
            Image i = new Image();
            BitmapImage src = new BitmapImage();
            i.Width = 1000;
            i.Height = 481;
            src.BeginInit();
            src.UriSource = new Uri(@"U:\Year 2 semester 1\multimodal interface work\MIG13_Practical04\MIG13_Practical04\tile.png", UriKind.Absolute);
            src.CacheOption = BitmapCacheOption.OnLoad;
            src.EndInit();
            i.Source = src;
            i.Stretch = Stretch.UniformToFill;
            int q = src.PixelHeight;        // Image loads here
            Canvas1.Children.Add(i);
        }

        private void Canvas1_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            Console.WriteLine("ok121223");
            Image sprite = new Image();
            sprite.Width = 38;
            sprite.Height = 32;

            sprite.Source = spriteSelected.Source;
            
            Point p = e.GetPosition(Canvas1);
            double x = p.X;
            double y = p.Y;
            p.X = p.X - (p.X % 27);
            p.Y = p.Y - (p.Y % 32);
            Canvas1.Children.Add(sprite);
            Console.WriteLine(x);
            Console.WriteLine(y);
            Canvas.SetTop(sprite, Math.Round(p.Y));
            Canvas.SetLeft(sprite, Math.Round(p.X));

        }



       private void Image_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            spriteSelected.Source = ((Image)sender).Source;
            Preview.Source = ((Image)sender).Source;
        }

        private void Canvas1_deleteImage(object sender, MouseButtonEventArgs e)
        {
            // checks if what is clicked is of datatype image
            if(e.Source is Image)
            {

                // creates placehold image and removes clicked image
                Image sprite = new Image();
                sprite = (Image)e.Source;
                Canvas1.Children.Remove(sprite);
            }
            
        }
    }
}
