import java.util.ArrayList;
import java.util.Arrays;
public class functions {
    public static void main(String[] args) { //como es static se colocan todas las funciones static
        //funciones
        for (int index = 0; index < 5; index++) {
            sendEmail();
        }
        sendEmail();
        sendEmailToUser("jdhbcwhdbciwe");
        sendEmailToUser("jdhbcwhdbciwe", "camila");
        var users = new ArrayList<String>(Arrays.asList("jdhbcwhdbciwe"));
        sendEmailToUser(users); 
        var state = sendEmailWhithReturn("jdhbcwhdbciwe");
        System.out.println(state);
        System.out.println(sendEmailWhithReturn("jdhbcwhdbciwe"));
        
    }
    // funciones sin parametros 
    static void sendEmail() {
        System.out.println("Enviando correo");
    }
    // funciones con parametros
    static void sendEmailToUser(String email) {
        System.out.println("Enviando correo a " + email);
    }
    //sobrecarga de funciones
    static void sendEmailToUser(String email, String name) {
        System.out.println("Enviando correo a " + email + " de " + name);
    }
    static void sendEmailToUser(ArrayList<String> emails) {
        for (String email : emails) {
            sendEmailToUser(email);
        }
    }
    //con retorno
    static boolean sendEmailWhithReturn(String email) {
        if (email.isEmpty()) {
            return false;
        }
        System.out.println("Enviando correo a" + email);
        return true;
    }
}
// si tennemos una logica que se repite ponemos en la funcion para llamar a otras funciones