import ui
import socket
import time

def sw1(s): 
	tx.sendto(bytes('1', 'utf-8'), (HOST, PORT))
	
def sw2(s): 
	tx.sendto(bytes('2', 'utf-8'), (HOST, PORT))

def sw3(s): 
	tx.sendto(bytes('3', 'utf-8'), (HOST, PORT))

def sw4(s): 
	tx.sendto(bytes('4', 'utf-8'), (HOST, PORT))

def sw5(s): 
	tx.sendto(bytes('0', 'utf-8'), (HOST, PORT))

def sw6(s): 
	tx.sendto(bytes('5', 'utf-8'), (HOST, PORT))
	
HOST, PORT = '192.168.4.1', 7000
rx = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
time.sleep(1)
rx.bind(('', 9000))

tx = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
on = '#ff6161'
off = '#5d5d5d'
v = ui.load_view()
v.present('sheet')
c = True

	
while True:
	d1 = str(rx.recv(12), 'utf-8')
	
	if d1.find('1H') > -1:
		v['button3'].background_color = on
		
	if d1.find('1L') > -1:
		v['button3'].background_color = off
	
	if d1.find('2H') > -1:
		v['button4'].background_color = on
		
	if d1.find('2L') > -1:
		v['button4'].background_color = off
	
	if d1.find('3H') > -1:
		v['button5'].background_color = on
		
	if d1.find('3L') > -1:
		v['button5'].background_color = off
		
	if d1.find('4H') > -1:
		v['button6'].background_color = on
		
	if d1.find('4L') > -1:
		v['button6'].background_color = off
		
	d1 = ''
		



