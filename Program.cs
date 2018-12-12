using System; // For Console, Int32, ArgumentException,Environment
using System.Net; // For IPAddress
using System.Net.Sockets; // For TcpListener, TcpClient
using System.Text; //For StringBuilder
using System.Threading;
using System.Collections.Generic;


namespace EchoServerTrackFever
{
	// State object for reading client data asynchronously  
	public class StateObject
	{
		// Client  socket.  
		public Socket workSocket = null;

		// Size of receive buffer.  
		public const int BufferSize = 50;
		// Receive buffer.  
		public byte[] buffer = new byte[BufferSize];
		// Received data string.  
		public StringBuilder sb = new StringBuilder();
	}

	public class UdpState
	{
		public IPEndPoint e;
		public UdpClient u;
	}



public class Player
{
		public Socket clientSocket;
		public IPEndPoint endpoint;
	public string playerName;
	public string playerPosX;
	public string playerPosY;
		public string playerLap;
		public string Wins;
		public string rotation;

	public Player()
	{
	}

	public void AddPlayer(string name)
	{
		playerName = name;

	}	
	
	}



	public class AsynchronousSocketListener
	{
		// Thread signal.  
		//dictionary for ll players on server
		public static Dictionary<int, Player> Players = new Dictionary<int, Player>();



		public static int count = 1;

		public static ManualResetEvent allDone = new ManualResetEvent(false);

		public AsynchronousSocketListener() {
		}

		// start listening for udp broadcasts
		public static void UdpStartListening()
		{
				UDPReceiveMessages();
	
		}

		public static void StartListening()
		{
			// Data buffer for incoming data.  
			byte[] bytes = new Byte[1024];

			// Establish the local endpoint for the socket.  
			// The DNS name of the computer  
			// running the listener is "host.contoso.com".  
			IPHostEntry ipHostInfo = Dns.GetHostEntry(Dns.GetHostName());
			IPAddress ipAddress = ipHostInfo.AddressList[0];
			IPEndPoint localEndPoint = new IPEndPoint(IPAddress.Any, 11100);

			// Create a TCP/IP socket.  
			Socket listener = new Socket(ipAddress.AddressFamily,
				SocketType.Stream, ProtocolType.Tcp);



			// Bind the socket to the local endpoint and listen for incoming connections.  
			try
			{
				listener.Bind(localEndPoint);
				listener.Listen(100);

				while (true)
				{
					// Set the event to nonsignaled state.  
					allDone.Reset();

					// Start an asynchronous socket to listen for connections.  
					Console.WriteLine("Waiting for a connection...");
					listener.BeginAccept(
						new AsyncCallback(AcceptCallback),
						listener);

					// Wait until a connection is made before continuing.  
					allDone.WaitOne();
				}

			}
			catch (Exception e)
			{
				Console.WriteLine(e.ToString());
			}

			Console.WriteLine("\nPress ENTER to continue...");
			Console.Read();

		}

		public static void AcceptCallback(IAsyncResult ar)
		{
			// Signal the main thread to continue.  
			allDone.Set();

			// Get the socket that handles the client request.  
			Socket listener = (Socket)ar.AsyncState;
			Socket handler = listener.EndAccept(ar);

			// Create the state object.  
			StateObject state = new StateObject();
			state.workSocket = handler;
			handler.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0,
				new AsyncCallback(ReadCallback), state);
		}

	

		public static void ReadCallback(IAsyncResult ar)
		{
			String content = String.Empty;
		
			// Retrieve the state object and the handler socket  
			// from the asynchronous state object.  
			StateObject state = (StateObject)ar.AsyncState;
			Socket handler = state.workSocket;

			// Read data from the client socket.   
			int bytesRead = handler.EndReceive(ar);

			if (bytesRead > 0)
			{
				// There  might be more data, so store the data received so far.  
				//state.sb.Append(Encoding.ASCII.GetString(
				//	state.buffer, 0, bytesRead));

				// Check for end-of-file tag. If it is not there, read   
				// more data.  
				content = Encoding.ASCII.GetString(state.buffer, 0, bytesRead);



				if (content.IndexOf(":") > -1)
				{
					// All the data has been read from the   
					// client. Display it on the console.  

					Console.WriteLine("Read {0} bytes from socket. \n Data : {1}",
					                  content.Length, content);

					//checks the contents and id the first string is add the player will add the player to the dictionary

					Char seperator = ':';
					// adds player to server dictionary
					string[] strings = content.Split(seperator);
					if (strings[0] == "ADD")
					{
						Player newplayer = new Player();
						Console.WriteLine("Adding player");
						newplayer.AddPlayer(strings[1]);
						newplayer.clientSocket = handler;

						Players.Add(count, newplayer);
						count += 1;
					}
					if (strings[0] == "WIN")
					{
						// assigns wins to the players who have completed three laps and sent the win message
						foreach (KeyValuePair<int, Player> entry in Players)
						{
							if (entry.Value.playerName == strings[1])
							{
								entry.Value.Wins = strings[2];

							}
						}

					}

					// send to everyone in the dictionary
				foreach(KeyValuePair<int, Player> entry in Players)
					{
						//Echo the data back to the client.  
						Send(entry.Value.clientSocket, content);
					}

				}


				// Not all data received. Get more.  
				handler.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0,
				new AsyncCallback(ReadCallback), state);
			}
		}

		public static bool messageReceived = false;

		/* here when we receive a udp message the server will split its contents and depending on the contents it will assign
		 * the values in the message to the players stored in a data dictionary
		 * also it reads the message sent
		 */

		public static void ReceiveUDPCallBack(IAsyncResult ar)
		{
			UdpClient u = (UdpClient)((UdpState)(ar.AsyncState)).u;
			IPEndPoint e = (IPEndPoint)((UdpState)(ar.AsyncState)).e;
			UdpState state = new UdpState();
			state.e = e;
			state.u = u;

			Byte[] receiveBytes = u.EndReceive(ar, ref e);
			string receiveString = Encoding.ASCII.GetString(receiveBytes);


			Console.WriteLine("Received UDP : {0}", receiveString);

			if (receiveString.IndexOf(":") > -1)
			{
				char seperator = ':';
				string[] strings = receiveString.Split(seperator);
				if (strings[1] == "MOVE")
				{
					foreach (KeyValuePair<int, Player> entry in Players)
					{
						if (strings[0] == entry.Value.playerName)
						{
							//float posx = float.Parse();
							entry.Value.endpoint = e;
							entry.Value.playerPosX = strings[2];
							entry.Value.playerPosY = strings[3];
							entry.Value.playerLap = strings[4];
							entry.Value.rotation = strings[5];
						}
					}
				}
				if (strings[0] == "RESET")
				{
					foreach (KeyValuePair<int, Player> entry in Players)
					{

					}
				}
				// send the positionbroadcasts to everyone in the game so they know of everyone in the server
			foreach (KeyValuePair<int, Player> entry in Players)
			{
					//Echo the data back to the client. 
					if (entry.Value.endpoint != null)
					{
						UdpSendMessage(entry.Value.endpoint, receiveString);
						//Send(handler, content);
					}
			}


			messageReceived = true;
				u.BeginReceive(new AsyncCallback(ReceiveUDPCallBack), state);
		}
		}

		public static void UDPReceiveMessages()
		{
			IPEndPoint e = new IPEndPoint(IPAddress.Any, 10000);
			UdpClient u = new UdpClient(e);

			UdpState s = new UdpState();
			s.e = e;
			s.u = u;



			Console.WriteLine("Listening for messages");
			u.BeginReceive(new AsyncCallback(ReceiveUDPCallBack), s);

			while (!messageReceived)
			{
				
			}
		}



		private static void UdpSendMessage(IPEndPoint client, string message)
		{
			UdpClient u = new UdpClient();

			u.Connect(client);
			Byte[] sendBytes = Encoding.ASCII.GetBytes(message);
			u.EnableBroadcast = true;
			u.BeginSend(sendBytes, sendBytes.Length, new AsyncCallback(UdpsendCallBack), u);

		}

		public static bool messageSent = false;
		private static void UdpsendCallBack(IAsyncResult ar)
		{
			UdpClient u = (UdpClient)ar.AsyncState;

			Console.WriteLine("number of bytes sent: {0}", u.EndSend(ar));
			messageSent = true;
		}

		private static void Send(Socket handler, String data)
		{
			// Convert the string data to byte data using ASCII encoding.  
			Console.WriteLine("Sending :{0}", data);
			byte[] byteData = Encoding.ASCII.GetBytes(data);

			// Begin sending the data to the remote device.  
			handler.BeginSend(byteData, 0, byteData.Length, 0,
				new AsyncCallback(SendCallback), handler);
		}

		private static void SendCallback(IAsyncResult ar)
		{
			try
			{
				// Retrieve the socket from the state object.  
				Socket handler = (Socket)ar.AsyncState;

				// Complete sending the data to the remote device.  
				int bytesSent = handler.EndSend(ar);
				Console.WriteLine("Sent {0} bytes to client.", bytesSent);

				//handler.Shutdown(SocketShutdown.Both);
				//handler.Close();

			}
			catch (Exception e)
			{
				Console.WriteLine(e.ToString());
			}
		}



		public static int Main(String[] args)
		{
			// starts the threads to start listening for tcp and udp
			Thread udpClientThread = new Thread(UdpStartListening);
			Thread tcpClientThread = new Thread(StartListening);

			udpClientThread.Start();
			tcpClientThread.Start();



			return 0;
		}
	}
}
