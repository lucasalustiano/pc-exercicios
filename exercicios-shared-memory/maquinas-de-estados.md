1 - Máquinas de estados - Discutimos a máquina de estados de processos de um sistema operacional UNIX. Agora, indique quais os estados que threads Java podem assumir. Discuta que eventos (incluindo chamadas de métodos) podem provocar mudanças de estado.

As threads em Java podem assumir os seguintes estados:

- NEW: Estado inicial que ocorre durante a instanciação da thread. Ocasionado por `new Thread()`.

- RUNNABLE: Estado em que a thread está rodando na JVM ou está pronta para rodar, onde a thread pode ou está esperando por recursos do SO ou esperando ser alocada para execução pelo scheduler da JVM. Ocasionado por `start()` após sua instanciação, por `notify()` ou `notifyAll()` invocado por uma outra thread para notificar threads em estado WAITING ou TIMED WAITING após a ocorrência de um determinado evento, fazendo com que a thread altere seu estado de WAITING ou TIMED WAITING para RUNNABLE, quando o tempo de sleep de uma thread no estado TIMED WAITING se encerra ou quando uma thread no estado BLOCKED ganha o monitor lock.

- BLOCKED: Estado em que a thread bloqueia esperando que o monitor lock entre em um método síncrono. Ocasionado quando uma thread tenta executar um método anotado como syncronized.

- WAITING: Estado em que uma thread espera indefinidamente por outra thread até que esta execute uma ação particular. Ocasionado pela chamada de `wait()`, `join()` ou `park()` por alguma thread RUNNABLE.

- TIMED WAITING: Estado em que uma thread espera por um determinado período de tempo por outra thread. Ocasionado pela chamada de `sleep()`, `wait()`, `join()`, `parkNanos()` ou `parkUntil()` por alguma thread RUNNABLE.

- TERMINATED: Estado em que a thread executou completamente ou ocorreu alguma exceção durante sua execução.
