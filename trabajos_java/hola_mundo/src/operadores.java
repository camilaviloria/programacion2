public class operadores {
    public static void main(String[] args) {
        //aritmeticos
        var a = 4;
        var b = 9;
    
        System.out.println(a + b);
        System.out.println(a - b);
        System.out.println(a * b);
        System.out.println(a / b);
        System.out.println(a % b);

        //asignacion
        a = b;
        System.out.println(a);

        a = b * 2;
        System.out.println(a);

        a += 1;
        System.err.println(a);

        a -= 1;
        System.err.println(a);
        a *= 1;
        System.err.println(a);
        a /= 1;
        System.err.println(a);

        // comparacion 
        System.out.println(a == b);
        System.out.println(a == 9);
        System.out.println(a != b);
        System.out.println(a > b);
        System.out.println(a < b);
        System.out.println(a >= b);
        System.out.println(a <= b);

        //logicos
        var c = true;
        var d = false;
        System.out.println(3<2 && 2 == 1); // AND
        System.out.println(4 < 2 || 2 == 3); // OR
        System.out.println(!c); // NOT
        System.out.println(!d); // NOT

        // operadores unarios
        System.out.println(+a);
        System.out.println(-a);
        System.out.println(++a);
        System.out.println(--a);

    }
}
