using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;

//namespace TcpListener01
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            IPAddress ip = IPAddress.Parse("127.0.0.1");
//            TcpListener tcpListener = new TcpListener(ip, 13);
//            Console.WriteLine("{0}", tcpListener.LocalEndpoint.ToString());
//            Console.ReadKey();
//        }
//    }
//}

namespace AcceptTcpClient01
{
    class Program
    {
        static void Main(string[] args)
        {
            TcpListener tcpListener = new TcpListener(IPAddress.Parse("192.168.0.9"), 13);
            tcpListener.Start();
            Console.WriteLine("대기 상태 시작");
            TcpClient tcpClient = tcpListener.AcceptTcpClient();
            Console.WriteLine("대기 상태 종료");
            tcpListener.Stop();
        }
    }
}