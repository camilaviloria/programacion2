public class functions {
    public static void main(String[] args) { //como es static se colocan todas las funciones static
        //funciones
        for (int index = 0; index < 5; index++) {
            sendEmail();
            sendEmailToUser("djncjkenjkcn@gmail.com");
        }
        //funcion sin parametros
        public static void sendEmail() {
            System.out.println("se envia el email");
            
        }
        //funcion con parametros
        public static void sendEmailToUser(String email) {
            System.out.println("se envia el email a " + email);
        }
    }
}