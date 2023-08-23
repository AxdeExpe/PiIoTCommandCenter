data.json at the server side has the information stored about the client

For example:

"worker":[
        {
            "ip":"127.0.0.1",
            "pwd":"admin",
            "rights":"sgf"
        }
    ]

ip: is the ip address of the worker
pwd: is the password of the worker
rights: are the rights of the worker
- s: can the worker send data? (example: files)
- g: can the worker request the gpio head of the server?
- f: can the worker read or write files on the server?

If somethingthe worker shouldn't has rights of something just write "-"

For example:
"rights":"s--"

--> the worker is only authorized to send data