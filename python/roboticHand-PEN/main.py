from cvzone.HandTrackingModule import HandDetector

import cv2
import math
import numpy
import serial
import io
import interpolacion

# ------------------------ SETUP CAMARA ------------------------
print("CARGANDO...")
cap = cv2.VideoCapture(0) # Abir la cámara (index 0)

#Si no se abre/detecta correctamente, insiste en abrir la cámara
while not cap.isOpened():
    input("conecte la cámara y presione ENTER para reintentar")
    cap = cv2.VideoCapture(0)

print("Cámara conectada!")
print("CARGANDO...")
print("Presione ENTER para cerrar el programa")
print("Presione N para cambiar el nivel de resolución mientras se ejecuta")

# Definir tamaño de imagen
anchoCamara, altoCamara = 1280, 720
cap.set(3, anchoCamara)
cap.set(4, altoCamara)
# ------------------------- FIN CAMARA -------------------------



# ----------------------- SETUP DETECCION -----------------------
detector = HandDetector(detectionCon=0.7, maxHands=1) # Fidelidad y cantidad de manos a detectar

falanges = [0, 4, 8, 12, 16, 20, 17] # muñeca, pulgar, indice, medio, anular, meñique, baseMeñique
x = [0] * 7
y = [0] * 7
dedos = ["pulgar ", "indice ", "medio  ", "anular ", "meñique"]
distancias = [0] * 5
# ------------------------ FIN DETECCION ------------------------



# --------------------- SETUP ENVIO EN SERIE ---------------------
listo = False
conexionSerie = False
recepcion = ''

ser = serial.serial_for_url('loop://', timeout=1)  # crea una instancia de serial.Serial que simula un puerto serie en memoria sin conexión física


usar = input("Quiere conectar en serie? (si | no): ")
if usar == "si":
    ser.close() # Cerra conexion falsa
    conexionSerie = True

    comUsuario = input("Ingresar puerto serie:")

    serial_port = "COM"+comUsuario
    try:
        # Abrir serial port
        ser = serial.Serial(serial_port, bytesize = 8, parity = serial.PARITY_NONE, stopbits=serial.  STOPBITS_ONE , baudrate = 115200)

        print(f"Conectado a {serial_port} a 115200 baudios") # Aviso al usuario

    except serial.SerialException as e:
        print(f"Error: {e}")
        input("Presiona Enter para reintentar...")
# ---------------------- FIN ENVIO EN SERIE ----------------------



# ------------------ SETUP MANIPULACION DE DATOS ------------------
# Con esto se setea la resolución (niveles de presición)
nivelMuestreo = input("Setee el nivel de resolución (niveles de presición)\n[1, 2, 3, 4, 5, 6, 7, 8]: ")
datosAEnviar = ['']*5  # Inicializo arreglo con caracteres vacíos
pasos = pow(2,int(nivelMuestreo))

# ------------------- FIN MANIPULACION DE DATOS -------------------


# ----------------------- INICIO DE PROGRAMA -----------------------
print("Iniciando cámara...")
hola = "a"+nivelMuestreo
if conexionSerie:
    ser.write(hola.encode())

while True:
    ret, fotograma = cap.read() # Capturar un fotograma de la cámara

    if not ret:
        break

    manos, fotograma = detector.findHands(fotograma) # Encontrar Mano en el fotograma
    # hands = detector.findHands(img, draw=False)  # sin dibujito

    if manos:
        mano = manos[0]

        contenedor = mano["bbox"] # Cuadro alrededor de la mano (coordenadas x,y,w,h)
        puntos = mano["lmList"] # puntos de las articulaciones

        # circulos de puntos de referencia
        for i in range(7):
            x[i] = puntos[falanges[i]][0]
            y[i] = puntos[falanges[i]][1]
            cv2.circle(fotograma, (x[i], y[i]), 10, (0, 255, 0), cv2.FILLED)

        # medicion de distancias entre los dedos y el punto de referencia
        for i in range(5):

            if i != 0:
                # Si el dedo no es el pulgar, uso la muneca como referencia
                cv2.line(fotograma, (x[0], y[0]), (x[i + 1], y[i + 1]), (255, 0, 0), 3)
                distancias[i] = math.hypot(x[i + 1] - x[0], y[i + 1] - y[0])
            else:
                # Si el dedo es el pulgar, uso la base del menique como referencia
                cv2.line(fotograma, (x[6], y[6]), (x[i + 1], y[i + 1]), (255, 0, 0), 3)
                distancias[i] = math.hypot(x[i + 1] - x[6], y[i + 1] - y[6])

            datosAEnviar[i] = chr(round(numpy.interp(distancias[i], [175, 425], [0, (pasos - 1)])) + 48)
            # numpy.interp Transforma un rango en otro
            # int, transforma en entero
            # chr, transforma en char (necesario porque sino no se guarda el valor como caracter)
            # + 48, ASCII, '0' = 48, ..., '9' = 57
            print(dedos[i],"    ",datosAEnviar[i])

        print("------------")

        # En caso de usar comunicacion en serie, se espera la recepcion para comenzar a enviar datos
        if conexionSerie:
            if ser.in_waiting > 0:
                recepcion = ser.read(1).decode()
                if recepcion == 'b':
                    print("b recibido, enviando")
                    for i in range(5):
                       # print(dedos[i], "enviado!")
                        ser.write(datosAEnviar[i].encode())  # Envía el dato

    # Mostrar el fotograma procesado
    cv2.imshow("imagen", fotograma)


    # Si se presiona la tecla ENTER, se cierra la ventana de la cámara
    tecla = cv2.waitKey(1) # Captura la tecla presionada
    if tecla == 13:  # 13 es el código ASCII de la tecla "ENTER"
        ser.close() # Cerrar conexión con puerto serie
        print("FIN DE PROGRAMA")
        break

    if tecla == 78 or tecla == 110:
        print("CAMARA EN PAUSA\n")
        ingreso = input("Ingrese nuevo nivel de muestreo: ")
        hola = "a"+ingreso
        pasos = pow(2,int(ingreso))

    if tecla == 114:
        ser.close()
        ser = serial.Serial(serial_port, bytesize=8, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE,
                            baudrate=115200)
        ser.write(hola.encode())

cap.release() # Cerrar el acceso a cámara
cv2.destroyAllWindows() # Cerrar la ventanas
# ------------------------ FIN DE PROGRAMA ------------------------