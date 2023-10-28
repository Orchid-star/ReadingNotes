data = bytes.fromhex('0060FC')

code_map = {0:'FC', 1:'60', 2:'BA', 3:'F2', 4:'66', 5:'D6', 6:'DE', 7:'70', 8:'FE', 9:'F6'}

def get_digital(value):
    a = value % 10
    b = int(value / 10) % 10
    c = int(value / 100) % 10   
    str_value = ''
    if (c != 0):
        str_value = code_map[c] + code_map[b] + code_map[a]
    elif (b != 0):
        str_value = '00' + code_map[b] + code_map[a]
    else:
        str_value = '0000' + code_map[a]
    return str_value

with open('ram.bin', 'wb') as file:
    for digital in range(0,256):
        data = int(get_digital(digital), 16)
        byte_data = data.to_bytes(3, byteorder='little')
        file.write(byte_data)