public class functions {
    public static void main(String[] args) { //como es static se colocan todas las funciones static
        //funciones
        for (int index = 0; index < 5; index++) {
            sendEmail();
        }
        sendEmail();
        sendEmailToUser("jdhbcwhdbciwe");
        sendEmailToUser("jdhbcwhdbciwe", "camila");
        var user =new ArrayList<String>(Arrays.asList("jdhbcwhdbciwe"));
        sendEmailToUser(user);
        
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
    static void sendEmailToUser(String[] emails) {
        for (String email : emails) {
            System.out.println("Enviando correo a " + email);
        }
    }
}