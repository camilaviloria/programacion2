
public class Loops {

    public static void main(String[] args) {
        for (int index = 0; index < 5; index++) {
            System.out.println(index);
        }

        for (int index = 0; index < 5; index++) {
            System.out.println("Hola, Java!");
        }

        String[] names = {"Brais", "Moure", "mouredev"};

        for (int index = 0; index < names.length; index++) {
            System.out.println(names[index]);
        }
        //while 
        int index = 0;
        while (index < 5) {
            System.out.println(index);
            index++;
        }
        index = 0;
        boolean find = false;
        while (find == true) {
            System.out.println(names[index]);
            if (names[index].equals("Moure")) {
                find = true;
            }
            index++;
        }
        do {
            System.out.println(names[index]);
            index++;
        } while (index < names.length);
        //control de bucles 
        for (String name : names) {
            if (name.equals("Moure")) {
                break;
            }
            System.out.println(name);
        }
        //-continue
        
        for (int i = 0; i < 5; i++) {
            if (i == 2) {
                continue;
            }
            System.out.println(i);
        }

    
    }
} 