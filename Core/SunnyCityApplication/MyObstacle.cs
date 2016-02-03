using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SunnyCityApplication
{
    public class CartesianCoordinate
    {
        public CartesianCoordinate()
        { }

        public CartesianCoordinate(double x, double y, double z)
        {
            m_x = x;
            m_y = y;
            m_z = z;
        }
        public double m_x;
        public double m_y;
        public double m_z;

        public LocalSystemCoordinate TranslateInLocalCoordinates()
        {
            LocalSystemCoordinate loc = new LocalSystemCoordinate();
            loc.m_a = Math.Atan(m_x / m_y);
            //double zen0 = 180 / Math.PI *  (Math.PI / 2.0 - Math.Atan(Math.Pow(8,0.5) / Math.Pow((Math.Pow(2, 2.0) + Math.Pow(2, 2.0)), 0.5)));
            loc.m_z = Math.PI / 2.0 - Math.Atan(m_z / Math.Pow((Math.Pow(m_x, 2.0) + Math.Pow(m_y, 2.0)), 0.5));
            return loc;
        }
    }

    public class LocalSystemCoordinate
    {
        public LocalSystemCoordinate() { }

        public LocalSystemCoordinate(double azimuth, double zenith)
        {
            m_a = azimuth;
            m_z = zenith;
        }
        public double m_a;
        public double m_z;
    }

    /// <summary>
    /// Hardcoded for Asnières
    /// </summary>
    public class MyObstacle
    {
        List<CartesianCoordinate> m_obstaclesCartesian = new List<CartesianCoordinate>();

        List<LocalSystemCoordinate> m_obstaclesLocal = new List<LocalSystemCoordinate>();

        double m_angleFromNorth;

        public MyObstacle()
        {
            m_angleFromNorth = 180;
            CartesianCoordinate point1 = new CartesianCoordinate(6, 3, 10);
            m_obstaclesCartesian.Add(point1);
            CartesianCoordinate point2 = new CartesianCoordinate(1, 3, 10);
            m_obstaclesCartesian.Add(point2);
            CartesianCoordinate point3 = new CartesianCoordinate(0, 2, 3);
            m_obstaclesCartesian.Add(point3);
            CartesianCoordinate point4 = new CartesianCoordinate(-6, 2, 6);
            m_obstaclesCartesian.Add(point4);
            CartesianCoordinate point5 = new CartesianCoordinate(-6, 5, 10);
            m_obstaclesCartesian.Add(point5);
            CartesianCoordinate point6 = new CartesianCoordinate(-20, 5, 10);
            m_obstaclesCartesian.Add(point6);

            foreach(CartesianCoordinate oneCart in m_obstaclesCartesian)
            {
                m_obstaclesLocal.Add(oneCart.TranslateInLocalCoordinates());
            }
        }

        public MyObstacle(string fileName)
        {
            string[] allLines = File.ReadAllLines(fileName);
            bool firstLine = true;
            foreach (string oneLine in allLines)
            {
                string[] data = oneLine.Split(';');
                if (firstLine == true)
                {
                    firstLine = false;
                    m_angleFromNorth = Convert.ToDouble(data[0]);
                }
                else
                {
                    m_obstaclesCartesian.Add(new CartesianCoordinate(Convert.ToDouble(data[0]), Convert.ToDouble(data[1]), Convert.ToDouble(data[2])));
                }
            }
            
            foreach (CartesianCoordinate oneCart in m_obstaclesCartesian)
            {
                m_obstaclesLocal.Add(oneCart.TranslateInLocalCoordinates());
            }
        }


        public double GetAngleFromNorth()
        {
            return m_angleFromNorth;
        }

        public double GetObstacleAngle(double azimuth)
        {
            double azimuthRadInMyCoordinate = (azimuth - GetAngleFromNorth())*Math.PI/180.0;
            LocalSystemCoordinate maxLocal = m_obstaclesLocal.First();
            LocalSystemCoordinate minLocal = m_obstaclesLocal.Last();
            foreach (LocalSystemCoordinate oneLocal in m_obstaclesLocal)
            {
                if (oneLocal.m_a <= azimuthRadInMyCoordinate && oneLocal.m_a >= minLocal.m_a)
                {
                    minLocal = oneLocal;
                }
                if (oneLocal.m_a >= azimuthRadInMyCoordinate && oneLocal.m_a <= maxLocal.m_a)
                {
                    maxLocal = oneLocal;
                }
            }
                        
            //TODO: trouver l'angle
            double estimatedZenithRad = minLocal.m_z + (maxLocal.m_z - minLocal.m_z) / (minLocal.m_a - maxLocal.m_a) * (minLocal.m_a - azimuthRadInMyCoordinate);
            return estimatedZenithRad;
        }


    }
}
