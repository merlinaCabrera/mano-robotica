import serial

numeroCom = input("Numero de Port:")
serial_port = "COM"+numeroCom
print("la veriable es:", serial_port)

try:
    # Abrir serial port
    ser = serial.Serial(serial_port, baudrate=115200, bytesize=8, stopbits=serial.STOPBITS_ONE, parity=serial.PARITY_NONE)
    print(f"Conectado a {serial_port}")

    # Datos a enviar
    datos = input("Ingresar datos a enviar: ")
    while datos != "0":
        ser.write(datos.encode())  # Formatear a bytes y enviar a serial port
        print("Datos enviados!")
        datos = input("Ingresar datos a enviar: ")
    ser.close()

    print("Conexión finalizada")

except serial.SerialException as e:
    print(f"Error: {e}")
    input("Presiona Enter para salir...")
