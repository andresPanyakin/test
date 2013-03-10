# Create your views here.
from django.shortcuts import render_to_response
import os
from apache_log_parser_regex import dictifyLogline
import operator

logDir = '/var/log/apache2'

def getLogDict(logline):
	l = dictifyLogline(logline)
	try:
		l['bytesSent'] = int(l['bytesSent'])
	except ValueError:
		bytesSent = 0
	l['logline'] = logline
	return l

def listFiles(request):
	file_list = [f for f in os.listdir(log_dir) if
			os.path.isfile(os.path.join(log_dir,f))]
	return render_to_response('list_files.html', {'file_list':file_list})

def viewLog(request, sortmethod, fileName):
	logFile = open(os.path.join(log_dir, fileName), 'r')
	logLines = [get_log_dict(l) for l in logFile]
	logFile.close()

	try:
		logLines.sort(key=operator.itemgetter(sortmethod))
	except KeyError:
		pass
	return render_to_response('view_logfile.html', {'loglines':logLines, 'filename':fileName})

