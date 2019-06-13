package TCPServer;

import java.io.IOException;
import java.net.ServerSocket;

/** The Server class
 * this is the main class
 * all interactions between server and client
 * goes with through this class*/
class Server {

/**    setting port number*/
    private static final int PORT_NUMBER = 1337;

/**  Creating a server socket object*/
    private static ServerSocket serverSocket;

/**   Creating a client handler object*/
    private static ClientHandler clientHandler;

    /**creating thread object*/
    private static Thread thread;

/** The main method
* used to host server on set host
* accepts connection of new clients
* and creates a new thread for each of them*/
    public static void main(String[] args) throws IOException {

        /**creates a new server socket on preset port value*/
        serverSocket = new ServerSocket(PORT_NUMBER);

        /**infinite loop*/
        while (true) {

            /**creates new client socket object
            * accepts the connection on the server */
            clientHandler = new ClientHandler(serverSocket.accept());
            System.out.println("connected");
            /** creates a new thread for the new client */
            thread = new Thread(clientHandler);

            /** starts the new thread*/
            thread.start();
        }
    }
/**The finalize method
* when the server is done
* this method ends the server connection*/
    protected void finalize() throws IOException {
        serverSocket.close();
    }
}