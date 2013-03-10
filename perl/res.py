#!/usr/bin/python
import re

data = open("king.in").read()
r = re.compile("^Subject: (B.*)+(.*a)+.*", re.IGNORECASE| re.MULTILINE );
m = r.search(data)
if m:
	print m.group(1)
	print m.group(2)
