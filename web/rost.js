﻿var h = void 0,
	i = null,
	l, crypto = require("crypto");
require("events");
var fs = require("fs"),
	http = require("http"),
	sql = require("sqlite3"),
	url = require("url"),
	util = require("util"),
	m = crypto.randomBytes(4).readUInt32LE(0);

function r(a, b) {
	var c = [];
	a.forEach(function (a) {
		c.push(b(a))
	});
	return c
}
function u(a, b) {
	var c = [];
	a.forEach(function (a) {
		b(a) && c.push(a)
	});
	return c
}
function v(a) {
	this.y = a
}
function w(a) {
	a.y ^= a.y << 13;
	a.y >>= 17;
	a.y ^= a.y << 5;
	return a.y
}

function x() {
	var a = fs.readFileSync("peers.txt", "utf8"),
		a = u(a.split("\n"), function (a) {
			return "string" == typeof a && 0 < a.length
		});
	return r(a, function (a) {
		a = a.split(" ");
		return {
			host: a[0],
			port: parseInt(a[1])
		}
	})
}
function y(a) {
	this.b = new v(a);
	this.key = w(this.b);
	this.i = 0
}
function z(a) {
	this.g = x();
	this.n = 0.6;
	this.b = new v(crypto.randomBytes(4).readUInt32LE(0));
	this.d = a
}

function A(a, b) {
	this.db = new sql.Database(a, sql.OPEN_READWRITE | sql.OPEN_CREATE, this.l.bind(this));
	this.b = new v(crypto.randomBytes(4).readUInt32LE(0));
	this.k = new y(w(this.b));
	this.o = b
}
util.inherits(A, require("events").EventEmitter);
A.prototype.l = function (a) {
	a !== i ? (util.error(a), process.exit(43)) : (this.db.run("CREATE TABLE IF NOT EXISTS flags ( flag TEXT, key INT )"), this.emit("init"))
};

function B(a) {
	var b = this;
	this.b = new v(a);
	this.e = "0123456789abcdef".split("");
	this.start = "a";
	this.c = {};
	r(this.e, function (a) {
		for (var d = b.c, e = b.e, f = b.b, g = e.slice(0), s = {}, n = 0; n < e.length; n++) {
			for (var p = w(f) % e.length; g[p] === h;) p = (p + 1) % g.length;
			s[e[n]] = g[p];
			g[p] = h
		}
		d[a] = s
	});
	this.b.y = crypto.randomBytes(4).readUInt32LE(0)
}
B.prototype.parse = function (a) {
	for (var b = this.start, c = 0; c < a.length; c++) b = this.c[b][a[c]];
	return b
};

function C(a) {
	for (var b = "", c = a.start, d = 0; 19 > d; d++) var e = a.e[w(a.b) % a.e.length],
		b = b + e,
		c = a.c[c][e];
	for (e in a.c[c]) if ("3" == a.c[c][e]) {
		b += e;
		break
	}
	return b
}
function G(a) {
	a === h && (a = 10);
	this.size = a;
	this.buffer = [];
	this.h = 0
}
G.prototype.add = function (a) {
	this.buffer[this.h] = a;
	this.h = (this.h + 1) % this.size
};
G.prototype.contains = function (a) {
	for (var b in this.buffer) if (this.buffer[b] === a) return !0;
	return !1
};

function H(a, b) {
	this.port = a;
	this.g = x();
	this.d = new B(9237503);
	this.db = new A(b, new z(this.d));
	this.j = new G(100)
}
l = H.prototype;
l.m = function (a, b) {
	a.on("end", function () {
		var c = url.parse(a.url, !0),
			d = u(c.pathname.split("/"), function (a) {
				return "" != a
			});
		if (0 == d.length) return this.error(b, 404, "Invalid path");
		if ("afd" == d[0]) {
			if (2 > d.length || 20 > d[1].length) return this.error(b, 404, "Invalid path");
			try {
				var e = this.d.parse(d[1]),
					f = {};
				f["5"] = this.q;
				f["8"] = this.t;
				f["3"] = this.s;
				f.a = this.r;
				f.f = this.p;
				if (f[e] === h) b.end();
				else {
					var g = d[1],
						s = f[e];
					this.j.contains(g) ? b.end(JSON.stringify({
						status: "failed",
						message: "I dontz likz replayz"
					})) : (this.j.add(g),
					s.call(this, a, b, c))
				}
			} catch (n) {
				return util.error(n), this.error(b, 500, "Internal Server Error")
			}
		} else b.end()
	}.bind(this))
};
l.q = function (a, b, c) {
	a = function (a, c) {
		a != i ? this.error(b, 500, a) : c !== h ? b.end(JSON.stringify({
			status: "success",
			id: c.rowid,
			flag: c.flag
		})) : b.end(JSON.stringify({
			status: "failed",
			error: "No value for this key"
		}))
	}.bind(this);
	this.db.db.get("SELECT rowid, flag FROM flags WHERE rowid = ?", [parseInt(c.query.id)], a)
};
l.t = function (a, b, c) {
	for (var d = this.db, e = function (a, c, d) {
		a == i ? b.end(JSON.stringify({
			status: "success",
			id: c,
			key: d
		}), "utf8") : this.error(b, 500, a)
	}.bind(this), f, a = d.k, c = new Buffer(String(c.query.flag)), g = 0; g < c.length; g++) c[g] ^= a.key;
	a.i = (a.i + 1) % 10;
	0 == a.i && (a.key = w(a.b));
	f = {
		key: a.key,
		cipher: c.toString("hex")
	};
	a = f.cipher;
	d.db.run("INSERT OR IGNORE INTO flags ( rowid, flag, key ) VALUES (?, ?, ?)", [crypto.randomBytes(4).readUInt32LE(0), a, 0], function (a) {
		if (a == i) {
			console.log("Storing: " + JSON.stringify(f) + " at key: " + this.lastID);
			var b = d.o,
				c = this.lastID,
				g = f.cipher;
			b.g = x();
			for (var t = Math.ceil(b.g.length * b.n), k = b.b, j = b.g.slice(0), D = [], E = 0; E < j.length; E++) {
				for (var q = w(k) % j.length; j[q] === h;) q = (q + 1) % j.length;
				D.push(j[q]);
				j[q] = h
			}
			var t = D.splice(0, t),
				F;
			for (F in t) k = t[F], util.debug("Replicating " + c + ": " + g + " to " + k.host + ":" + k.port), j = http.request({
				hostname: k.host,
				port: k.port,
				path: "/afd/" + C(b.d) + "?flag=" + g + "&id=" + c + "&" + (351142).toString(28) + "=" + m
			}, function (a) {
				var b = "";
				a.on("data", function (a) {
					a !== h && (b += a.toString("utf8"))
				});
				a.on("end", function (a) {
					a !== h && (b += a.toString("utf8"));
					console.log("Reply to replicate request: " + b)
				})
			}), j.on("error", function (a, b) {
				util.error("Error replicating data: ID " + c + " to " + a.host + ":" + a.port + " with error: " + b.message)
			}.bind(b, k)), j.end();
			e(a, this.lastID, f.key)
		} else e(a, 0, "")
	})
};
l.s = function (a, b, c) {
	a = String(c.query.flag);
	c = parseInt(String(c.query.id));
	(c === h || a === h) && this.error(b, 400, "Bad Request");
	console.log("Replicate: " + c + " -> " + a);
	var d = function (a) {
		a == i ? b.end(JSON.stringify({
			status: "success"
		})) : (util.error("Error replicating flag: " + a.toString("utf8")), this.error(b, 500, a))
	}.bind(this);
	this.db.db.run("INSERT OR IGNORE INTO flags ( rowid, flag, key ) VALUES (?, ?, ?)", [c, a, 0], d)
};
l.r = function (a, b) {
	b.end(JSON.stringify({
		status: "success",
		my_id: m
	}))
};
l.p = function (a, b) {
	this.db.u(function (a, d) {
		a == i ? b.write("ID: " + d.rowid + " FLAG: " + d.flag) : b.end()
	}, function () {
		b.end()
	})
};
l.error = function (a, b, c) {
	a.writeHead(b, c);
	a.end()
};
l.start = function () {
	http.createServer(this.m.bind(this)).listen(I)
};
var I = 8080,
	J = "data.sqlite";
isNaN(parseInt(process.argv[2])) || (I = parseInt(process.argv[2]), process.argv[3] !== h && (J = process.argv[3]));
(new H(I, J)).start();