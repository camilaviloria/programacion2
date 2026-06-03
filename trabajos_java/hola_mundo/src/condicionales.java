public class condicionales {
    public static void main(String[] args) {
        // condicionales (secuencias)
        var edad = 18;
        if (edad > 18) {
            System.out.println("es mayor de edad");
        } else if (edad == 18) {
            System.out.println("tiene 18 años");
        } else {
            System.out.println("es menor de edad");
        } 

        //switch

        var dia = 3;
        switch (dia) {
            case 1:
                System.out.println("lunes");
                break;
            case 2:
                System.out.println("martes");
                break;
            case 3:
                System.out.println("miercoles");
                break;
            default:
                System.out.println("dia no valido");
                break;
        }

    }
}
