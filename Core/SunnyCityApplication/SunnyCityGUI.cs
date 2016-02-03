using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace SunnyCityApplication
{
    public partial class SunnyCityGUI : Form
    {
        public SunnyCityGUI()
        {
            InitializeComponent();
            textBox_Longitude.Text = "2,2854";
            textBox_Latitude.Text = "48,91";
            textBox_Elevation.Text = "50";
            
        }

        private InputParams GetSample()
        {
            InputParams spa = new InputParams();
            spa.year = 2003;
            spa.month = 10;
            spa.day = 17;
            spa.hour = 12;
            spa.minute = 30;
            spa.second = 30;
            spa.timezone = -7.0;
            spa.delta_ut1 = 0;
            spa.delta_t = 67;
            spa.longitude = -105.1786;
            spa.latitude = 39.742476;
            spa.elevation = 1830.14;
            spa.pressure = 820;
            spa.temperature = 11;
            spa.slope = 30;
            spa.azm_rotation = -10;
            spa.atmos_refract = 0.5667;
            spa.function = 3;// SPA_ALL;
            return spa;
        }

        private InputParams GetInputData()
        {
            InputParams spa = new InputParams();
            spa.year = 2015;
            spa.month = 06;
            spa.day = 30;
            spa.hour = 13;
            spa.minute = 47;
            spa.second = 0;
            spa.timezone = +2.0;
            spa.delta_ut1 = 0;
            spa.delta_t = 67;
            spa.longitude = 2.2854;
            spa.latitude = 48.91;
            spa.elevation = 50;
            spa.pressure = 1015;
            spa.temperature = 18;
            spa.slope = 0;
            spa.azm_rotation = 0;
            spa.atmos_refract = 0.5667;
            spa.function = 3;// SPA_ALL;
            return spa;
        }

        private InputParams GetInputParams()
        {
            InputParams input = GetInputData();
            input.latitude = Convert.ToDouble(textBox_Latitude.Text);
            input.longitude = Convert.ToDouble(textBox_Longitude.Text);
            input.elevation = Convert.ToDouble(textBox_Elevation.Text);
            input.day = dateTimePicker1.Value.Day;
            input.month = dateTimePicker1.Value.Month;
            input.year = dateTimePicker1.Value.Year;
            input.hour = dateTimePicker1.Value.Hour;
            input.minute = dateTimePicker1.Value.Minute;
            if (checkBox1.Checked == true)
            {
                input.hour = input.hour - 1;
            }
           
            if( input.hour < 0)
            {
                input.hour = 0; //anyway, it is the nigth
            }
            return input;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //Test with the parameters given by the C++ guy
            //InputParams inputSample = GetSample();

            InputParams input = GetInputParams();
            
            OutputParams res = InputParams.spa_calculate(input);

            richTextBox1.Clear();
            richTextBox1.AppendText("Azimuth:" + res.azimuth);
            richTextBox1.AppendText(Environment.NewLine);
            richTextBox1.AppendText("Zenith:" + res.zenith);

            bool isSunny = false;
            MyObstacle obstacle = new MyObstacle(m_fileName);
            double obstacleZenith = obstacle.GetObstacleAngle(res.azimuth) * 180 / Math.PI;
            if (res.zenith < obstacleZenith)
            {
                isSunny = true;
                richTextBox1.AppendText(Environment.NewLine);
                richTextBox1.AppendText("Soleil");
            }
            else
            {
                isSunny = false;
                richTextBox1.AppendText(Environment.NewLine);
                richTextBox1.AppendText("Ombre");
            }


    //             public double azimuth;
    //public double b;
    //public double del_epsilon;
    //public double del_psi;
    //public double epsilon;
    //public double h;
    //public double incidence;
    //public double jd;
    //public double l;
    //public double r;
    //public double sunrise;
    //public double sunset;
    //public double zenith;
        }


        string m_fileName;
       

        private void button2_Click(object sender, EventArgs e)
        {
            openFileDialog1.InitialDirectory = Application.StartupPath + "\\ObstaclesFiles";
            if( openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                m_fileName = openFileDialog1.FileName;
                textBox_ObstaclesFile.Text = m_fileName;
            }

        }

        private void button_SimulateOneDay_Click(object sender, EventArgs e)
        {
            chart1.Series.Clear();
            chart1.Series.Add("Sunny Data");

            MyObstacle obstacle = new MyObstacle(m_fileName);
            InputParams input = GetInputParams();
            input.hour = 0;
            input.minute = 0;
            while (input.hour < 24)
            {
                input.minute = input.minute + 10;
                if (input.minute > 59)
                {
                    input.minute -= 60;
                    input.hour += 1;
                }

                OutputParams res = InputParams.spa_calculate(input);
                bool isSunny = false;
                double obstacleZenith = obstacle.GetObstacleAngle(res.azimuth) * 180 / Math.PI;
                if (res.zenith < obstacleZenith)
                {
                    isSunny = true;
                }
                else
                {
                    isSunny = false;
                }
                DataPoint Dp = new DataPoint();
                Dp.SetValueXY(input.hour + input.minute/60.0, isSunny);

                chart1.Series["Sunny Data"].Points.Add(Dp);
           }

           
        }
    }
}
