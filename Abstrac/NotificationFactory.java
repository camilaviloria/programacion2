package Abstrac;
// permite producir fammilias de objetos relacionados sin especificar sus clases
// El cliente trabaja con las interfaces abstractas, declara un grupo de meosdos para crear cada uno de los productos
public interface NotificationFactory {
    Email crearEmail();
    SMS crearSMS();
}


