import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.Arrays;
import java.util.Scanner;

class Client {
    public static void main(String argv[]) throws Exception {
        String sentence="connected";
        Socket clientSocket = new Socket("localhost", 1337);
        DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
        Scanner inFromUser = new Scanner(System.in);
        BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            outToServer.writeBytes("hey\n");
        clientSocket.close();
        inFromUser.close();
        outToServer.close();
        inFromServer.close();
    }
}