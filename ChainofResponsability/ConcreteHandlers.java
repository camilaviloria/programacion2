package ChainofResponsability;

// Manejador Nivel 1: Problemas básicos
class ConcreteHandlers extends BaseHandler {
    @Override
    public void handle(String request) {
        if (request.equalsIgnoreCase("Contraseña olvidada")) {
            System.out.println("[Soporte Nivel 1]: Resuelto -> Restableciendo contraseña.");
        } else {
            // Llama a parent::handle(request) como en el diagrama
            super.handle(request);
        }
    }
}

// Manejador Nivel 2: Problemas de red o software
class SoporteTecnicoHandler extends BaseHandler {
    @Override
    public void handle(String request) {
        if (request.equalsIgnoreCase("Fallo en la red")) {
            System.out.println("[Soporte Nivel 2]: Resuelto -> Reiniciando el servidor de red.");
        } else {
            super.handle(request);
        }
    }
}

// Manejador Nivel 3: Decisiones de presupuesto o hardware
class GerenciaHandler extends BaseHandler {
    @Override
    public void handle(String request) {
        if (request.equalsIgnoreCase("Compra de Servidor")) {
            System.out.println("[Gerencia]: Resuelto -> Aprobando presupuesto para servidor.");
        } else {
            super.handle(request);
        }
    }
}
