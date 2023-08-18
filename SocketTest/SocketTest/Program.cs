using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;

//namespace IPAddress01
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            string Address = Console.ReadLine();
//            IPAddress IP = IPAddress.Parse(Address);
//            Console.WriteLine("ip : {0}", IP.ToString());
//        }
//    }
//}

//namespace DNS
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//
//            IPAddress[] IP = Dns.GetHostAddresses("www.naver.com");
//            foreach(IPAddress HOSTIP in IP)
//                Console.WriteLine("ip : {0}", HOSTIP.ToString());
//        }
//    }
//}

namespace IPHostEntry01
{
    class Program
    {
        static void Main(string[] args)
        {

            IPHostEntry HashInfo = Dns.GetHostEntry("www.naver.com");
            foreach (IPAddress ip in HashInfo.AddressList)
                Console.WriteLine("ip : {0}", ip.ToString());
            Console.WriteLine("ip : {0}", HashInfo.HostName);
        }
    }
}

namespace IPHostEndPoint01
{
    class Program
    {
        static void Main(string[] args)
        {
            IPAddress ipInfo = IPAddress.Parse("127.0.0.1");
            int port = 13;
            IPEndPoint endPointInfo = new IPEndPoint(ipInfo, port);
            Console.WriteLine("ip: {0} port: {1}", endPointInfo.Address, endPointInfo.Port);
            Console.WriteLine(endPointInfo.ToString());
            Console.ReadKey();
        }
    }
}