#coding=utf-8
from time import sleep
from  dpkt import *
from  struct import pack, unpack

def crc16(bytes):
	crc = 0xFFFF
	polynomial = 0x1021
	for b in bytes:
		b = unpack( "B", b)[0]
		for i in range(0, 8):
				bit = ((b   >> (7-i) & 1) == 1);
				c15 = ((crc >> 15    & 1) == 1);
				crc <<= 1;
				if (c15 ^ bit):
					crc ^= polynomial;
	crc &= 0xffff
	return crc

#Обработка tcp пакета, включащего в себя несколько synphasor-пакетов.
def extractTcpTimeStamp( buf ):
	seek = 0
	offset = 0
	packs = []
	Pack = ethernet.Ethernet( buf )

	while seek < len( Pack.data.data.data ):
		if Pack.data.data.data[ seek ] == '\xaa':
			offset = unpack( '!H', Pack.data.data.data[ seek + 2 : seek + 4] )[ 0 ]
			#Создаем такой же Tcp пакет и в него инкапсулируем n-й synphasor-пакет.
			tmp = ethernet.Ethernet( buf )
			tmp.data.data.data = Pack.data.data.data[ seek : seek + offset ]
			packs.append( tmp )
			seek += offset
	return packs

def extractSynPhasorTimeStamp( buf ):
	pass

def main():
	f = open("timewave-zero.pcap")
	f1 = open("dump.pcap", 'w')
	seek = 0
	offset = 0
	reasm = 0
	reasmOffset = 0

	#Create dump objects
	packet = pcap.Reader(f)
	wpack = pcap.Writer(f1)

	for ts, buf in packet:
		tmp = ethernet.Ethernet(buf)
		tcpData = tmp.data.data.data
		if len( tcpData ) > 0:
			print len( tcpData )
			while seek < len( tcpData ):

				if reasm == 1:
					checkSum = crc16( cache[:-2] + tcpData[:-2] )
					timestamp = 
					#else:
					#	checkSum = crc16( tcpData)

					tmp.data.data.data = tmp.data.data.data[ : - 2] + pack( '!H', checkSum ) 
					#+ tmp.data.data.data[ reasmOffset : ]
					reasm = 0
					reasmOffset = 0

				#Synphasor data starts with 'aa' byte
				if tmp.data.data.data[seek] == '\xaa':
					synPack = tmp.data.data.data
					offset = unpack( '!H', synPack[ seek + 2 : seek + 4 ] )[ 0 ]

					if offset > len( tcpData):
						reasm = 1
						reasmOffset = offset - len( tcpData )
						cache = tcpData


					#Calculate correct checksum of the synphasor packet and replace the wrong one.
					checkSum = crc16(tmp.data.data.data[ seek : seek + offset - 2 ] )
					timestamp = 
					tmp.data.data.data = tmp.data.data.data[ : seek + offset - 2] + pack( '!H', checkSum ) + tmp.data.data.data[ seek + offset : ]
					seek += offset
				else:
					break
			cache = tmp.data.data.data[ seek-offset : seek + offset ]
			if len(cache) > 90 and len(cache) < 100:
				reasm = 1
				reasmOffset = len(cache)

			seek = 0
			offset =0
		wpack.writepkt( tmp )
	f.close()
	f1.close()

if __name__ == '__main__':
	main()