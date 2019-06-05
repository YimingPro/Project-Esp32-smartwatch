package TCPServer;

import java.lang.Runnable;
import java.net.Socket;
import java.io.*;

/** ClientHandler Class
 * Used to receive data from client
 * after receiving part is done, the data will be processed for the further usage*/
class ClientHandler implements Runnable {

    /** local class object
     * client socket*/
    private Socket clientSocket;

    /** constructor of the ClientHandler class*/
    ClientHandler(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }

    /** this is the main method of this function
     * all in/out interaction happens here
     * all received data is passed to other methods and classes here*/
    public void run() {

        /** local function string variable
        String clientSentence = "";

        /** input and output buffer for the client*/
        try (
                /** creating an input buffer for the client*/
                BufferedReader inFromClient =
                     new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

                /** creating an output buffer for the client*/
                DataOutputStream outToClient =
                        new DataOutputStream(clientSocket.getOutputStream());
        ){
            /** while client is connected  the following code will execute*/
            while (clientSocket.isConnected()){

                /** getting data from client*/
                String temp = inFromClient.readLine();

                /** printing out received data in upper case*/
                System.out.println(temp.toUpperCase());

            }
            /** closing input buffer for the client*/
            inFromClient.close();
            /** closing output buffer for the client*/
            outToClient.close();

        } catch (IOException e){
            e.printStackTrace();
        }

        finally {
            try {
                /** close client socket*/
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    /** this method returns client socket*/
    public Socket getClient() {
        return clientSocket;
    }
}