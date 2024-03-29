

<!-- ########## START OF CHAPTER: 000 ########## -->
<details> <!-- OBJECTIVE -->
<summary>Objective</summary>

- Basic Understanding of Backend Engineering

</details>
<!-- ########## END OF CHAPTER: 000 ########## -->


<!-- ########## START OF CHAPTER: 002 ########## -->
<details>
<summary>002 - Backend Communication Design Patterns</summary>

<!-- ##### START OF TOPIC: Request-Response ##### -->
<details>
<summary>Request-Response</summary>

## Request Response Model
- Client sends a Request
- Server parses the Request (Ex: parse)
- Server processes the Request (Ex: query db, deserialization)
- Server sends a Response
- Client parses the Response and consume
## Where it is used?
- Web, HTTP, DNS, SSH
- RPC (remote procedure call)
- SQL and Database Protocols
- APIs (REST/SOAP/GraphQL)
## Examples:
### Building an upload image service with request response
- Send large request with the image (simple, not resumable)
- Chunk image and send a request per chunk (resumable with unique identifier)
### Request Response doesn't work everywhere (Not scalable, latency)
- Notification service
- Chatting application
- Very long requests
- What if client disconnects?

## curl example
- curl -v --trace out.txt http://google.com
- cat out.txt

</details>
<!-- ##### END OF TOPIC: Request-Response ##### -->

<!-- ##### START OF TOPIC: Synchronous vs Asynchronous  ##### -->
<details>
<summary>Synchronous vs Asynchronous</summary>

- Can I do work while waiting?
# Synchronous I/O
- Caller sends a request and blocks
- Caller cannot execute any code meanwhile
- Receiver responds, Caller unblocks
- Caller and Receiver are in "sync"
## Example of an OS synchronous I/O
- Program asks OS to read from disk
- Program main thread is taken off of the CPU
- Read completes, program can resume execution

# Asynchronous I/O
- Caller sends a request
- Caller can work until it gets a response
- Caller either:
- - Checks if the response is ready (epoll)
- - Receiver calls back when it's done (io_uring)
- - Spins up a new thread that blocks
- Caller and receiver are not necessary in sync

## Example of an OS asynchronous call (NodeJS)
- Program spins up a secondary thread
- Secondary thread reads from disk, OS blocks it
- Main program still running and executing code
- Thread finish reading and calls back main thread

# Synchronous vs Asynchronous in Request Response
- Synchronicity is a client propert
- Most modern client libraries are asynchronous
- Ex: Clients send an HTTP request and do work

# Synchronous vs Asynchronous in real life
- In synchronous communication the caller waits for a response from receiver
- - ex: Asking someone a question in a meeting
- Asynchronous communication the response can come whenever. Caller and receiver  can do anything meanwhile
- - email

# Asynchronous workload is everywhere
- Asynchronous Programming (promises/futures)
- Asynchronous backend processing
- Asynchronous commits in postgres
- Asynchronous IO in Linux (epoll, io_uring)
- Asynchronous replication
- Asynchronous OS fsync (fs cache)

# DEMO

</details>
<!-- ##### END OF TOPIC: Synchronous vs Asynchronous ##### -->

<!-- ##### START OF TOPIC: PUSH ##### -->
<details>
<summary>Push</summary>

# Request/response isn't always ideal
- Client wants real time notification from backend
- - A user just logged in
- - A message is just received
- Push model is good for certain cases (Ex: Chat app)

# What is Push
- Client connects to a server
- Server sends data to the client
- Client doesn't have to request anything
- Protocol must be bidirectional
- Used by RabbitMQ

# Push Pros and Cons
- Pros
- - Real time
- Cons
- - Clients must be online
- - Clients might not be able to handle
- - Requires a bidirectional protocol
- - Polling is preferred for light clients

# DEMO

</details>
<!-- ##### END OF TOPIC: PUSH ##### -->

<!-- ##### START OF TOPIC: POLLING ##### -->
<details>
<summary>Polling</summary>

- A request takes long time to process
- - Upload a youtube video
- The backend want to sends notification
- - A user just logged in

# What is Short Polling
- Client sends a request
- Server responds immediately with a handle
- Server continues to process the request
- Client uses that handle to check for status
- Multiple "short" request response as polls

# Short Polling Pros and Cons
- Pros
- - Simple
- - Good for long running requests
- - Client can disconnect
- Cons
- - Too chatty (Many client adds up request & network will be congested)
- - Network bandwidth
- - Wasted Backend resources

# DEMO

</details>
<!-- ##### END OF TOPIC: POLLING ##### -->


<!-- ##### START OF TOPIC: LONG POLLING ##### -->
<details>
<summary>Long Polling</summary>

- Request is taking long, I'll check with you later But talk to me only when it's ready
# What is Long Polling?
- Client sends a request
- Server responds immediately with a handle
- Server continues to process the request
- Server DOES not reply until it has the response
- So we got a handle, we can disconnect and we are less chatty
- Some variation has timeouts too

# Long Polling Pros and Const
- Pros
- - Less chatty and backend friendly
- - Client can still disconnect
- Cons
- - Not real time

# DEMO

</details>
<!-- ##### END OF TOPIC: LONG POLLING ##### -->


<!-- ##### START OF TOPIC: Server Sent Events ##### -->
<details>
<summary>Server Sent Events</summary>

- One Request, a very very long response

# Limitations of Request/Response
- Vanilla Request/response isn't ideal for notification backend
- Client wants real time notification from backend
- - A user just logged in
- - A message is just received
- Push works but restrictive
- Server Sent Events work with Request/Response
- Designed for HTTP

# What is Server Sent Events?
- A response has start and end
- Client sends a request
- Server sends a logical events as part of response
- Server never writes the end of the response
- It is still a request but an unending response
- Client parses the streams data looking for event
- Works with Request/Response (HTTP)

# Server Sent Events Pros and Cons
- Pros
- - Real time
- - Compatible with Request/Response
- Cons
- - Clients must be online
- - Clients might not be able to handle
- - Polling is preferred for light clients
- - HTTP/1.1 problem (6 connections)

# DEMO

</details>
<!-- ##### END OF TOPIC: Server Sent Events ##### -->


<!-- ##### START OF TOPIC: Publish Subscribe ##### -->
<details>
<summary>Publish Subscribe</summary>

- One publisher many readers

# Request/Response pros and cons
- Pros
- - Elegant and Simple
- - Scalable
- Cons
- - Bad for multiple receivers
- - High Coupling
- - Client/Server have to be running
- - Chaining, circuit breaking (Complex logic)

# Pub/Sub
## Pub/Sub pros and const
- Pros
- - Scales with multiple receivers
- - Great for microservices
- - Loose Coupling (Client is not directly connected to server)
- - Works while clients not running
- Cons
- - Message delivery issues
- - Complexity (ex: Adding partion, Scaling)
- - Network saturation (ex: Polling & network congestion)

## RabbitMQ DEMO


</details>
<!-- ##### END OF TOPIC: Publish Subscribe ##### -->


<!-- ##### START OF TOPIC: Multiplexing vs Demultiplexing ##### -->
<details>
<summary>Multiplexing vs Demultiplexing </summary>

- HTTP/2, QUIC, Connection Pool, MPTCP

# Multiplexing example HTTP/2
- User sends 3 request
- Chrome opens multiple connections
- - Case 1: Server with HTTP/1.1 => 3 Channels  (Not Multiplex, Create connection 1 by 1)
- - Case 2: Server with HTTP/2 => Only 1 connection(Multiplex, 3 stream fed to 1 pipe)

## Multiplexing HTTP/2 on the Backend
- |User| -> 3 HTTP/1.1 Connections => |Proxy| => 1 HTTP/2 Connection => |HTTP/2 server|
- More throughput
- High backend resources (CPU for HTTP/2 server)

## Demultiplexing HTTP/1.1 on the Backend
- |User| -> 1 HTTP/2 Connection => |Proxy| => 3 HTTP/1.1 Connections=> |HTTP/2 server|
- less throughput
- low backend resources (simple h1)

# Connection Pooling
- Demultiplexing
- Ex: Can spin up database connection
- - Query is blocked if all of the connections are busy

# Browser demultiplexing in HTTP/1.1
- Chrome allows up to 6 connections per domain, user's requests are demultiplexed in the 6 connections

## Browser connection pool DEMO


</details>
<!-- ##### END OF TOPIC: Multiplexing vs Demultiplexing ##### -->


<!-- ##### START OF TOPIC: Stateless vs Stateful ##### -->
<details>
<summary>Stateless vs Stateful </summary>

- Is state stored in the backend?
# Stateful vs Stateless backend
- Stateful
- - Stores state about clients in its memory
- - Depends on the information being there
- Stateless
- - Client is responsible to "transfer the state" with every request
- - May store but can safely lose it

# Stateless Backends
- Stateless backends can still store data somewhere else
- Can you start the backend during idle time while the client workflow continues to work?

# What makes a backend stateless?
- Stateless backends can store state somewhere else (database)
- The backend remains stateless but the system is stateful
- Can you restart the backend during idle time and the client workflow continue to work?

# Stateful backend
- Sesion/Cookie authentication

# Stateless vs Stateful protocols
- The Protocols can be designed to store state
- TCP is stateful (Every segments are labeled as sequence & stored in state)
- - Sequences, Connection file descriptor
- UDP is stateless
- - DNS send queryID in UDP to identify queries
- - QUIC sends connectionID to identify connection
- You can build a stateless protocol on top of a stateful one and vice versa
- HTTP on top of TCP
- If TCP breaks, HTTP blindly create another one
- QUIC on top UDP

# Complete Stateless System
- Stateless Systems are rare
- State is carried with every request
- A backend service that relies completely on the input
- - Check if input param is a prime number
- JWT (JSON Web Token)

</details>
<!-- ##### END OF TOPIC: Stateless vs Stateful  ##### -->

<!-- ##### START OF TOPIC: Sidecar Pattern ##### -->
<details>
<summary>Sidecar Pattern</summary>

- Thick clients, Thicker backends

# Every protocol requires a library

# Changing the libary is hard
- Once you use the library your app is entrenched
- App & Library should be the same language
- Changing the library requires retesting
- Breaking changes Backward compatibility
- Adding features to the library is hard
- Microservices suffer

# What if we delegate communication?
- Proxy communicate instead
- Proxyt has the rich library
- Client has thin libary (ex: http/1.1)
- Meet Sidecar pattern
- Each client must have a sidecar proxy

## Sidecar Design Pattern
- Sidecar Proxy with HTTP/2 + TLS Library
- |{HTTP/1.1 Client} <=> {Client sidecar Proxy}| <=(HTTP/2 + Secure Connection)=> |{Server sidecar Reverse Proxy} <=> http/1.1 Server|
- No change in both  client and server code, just the proxies But introduces an extra hop

# Sidcar Examples
- Service Mesh Proxies
- - Linkerd, Istio, Envoy
- Sidecar Proxy Container
- Must be Layer 7 Proxy

# Pros & Cons of Sidecar proxy
- Pros
- - Language agnostic (polyglot)
- - Protocol upgrade
- - Security
- - Tracing and Monitoring
- - Service Discovery
- - Caching
- Cons
- - Complexity
- - Latency

</details>
<!-- ##### END OF TOPIC: Sidecar Pattern ##### -->



</details>
<!-- ########## START OF CHAPTER: 002 ########## -->



<!-- ########## START OF CHAPTER: 003 ########## -->
<details>
<summary>003 - Backend Communication Design Patterns</summary>

<!-- ##### START OF TOPIC: PROTOCOL PROPERTIES ##### -->
<details>
<summary>Protocol Properties</summary>

# What is a protocol?
- A system that allows two parties to communicate
- A protocol is designed with a set of perperties
- Depending on the purpose of the protocol
- TCP, UDP, HTTP, gRPC, FTP

# Protocol properties
- Data format
- - Text based (plain text, JSON, XML)
- - Binary (protobuf, RESP, http2, http3)
- Transfer mode
- - Message based (UDP, HTTP)
- - Stream (TCP, WebRTC)
- Addressing system
- - DNS name, IP, MAC
- DIrectionality
- - Bidirectional (TCP)
- - Unidirectional (HTTP)
- - Full/Half duplex
- State
- - Stateful (TCP, gRPC, apache thrift)
- - Stateless (UDP, HTTP)
- Routing
- - Proxies, Gateways
- Flow & Congestion control
- - TCP (Flow & Congestion)
- - UDP (No control)
- Error management
- - Error code
- - Retries and timeouts

</details>
<!-- ##### END OF TOPIC: PROTOCOL PROPERTIES ##### -->


<!-- ##### START OF TOPIC: OSI MODEL ##### -->
<details>
<summary>OSI MODEL</summary>

- Open Systems Interconnection model

# Why do we need a communication model?
- Agnostic application
- - Without a standard model, your application must have knowledge of the underlying network medium
- - Imagine if you have to author different version of your apps so that it works on wifi vs ethernet vs LTE vs fiber
- Network Equipment Management
- - Without a standard model, upgrading network equipments becomes difficult
- Decoupled Innovation
- - Innovations can be done in each layer separately without affecting the rest of the models

# What is the OSI Model?
- 7 Layers each describe a specific networking component
- Layer 7 - Application - HTTP/FTP/gRPC (Most of the time as a backend developer)
- Layer 6 - Presentation - Encoding, Serialization
- Layer 5 - Session - Connection establishment, TLS
- Layer 4 - Transport - UDP/TCP (Most of the time as a backend developer)
- Layer 3 - Network - IP
- Layer 2 - Data link - Frames, Mac address Ethernet
- Layer 1 - Physical - Electric signals, fiber or radio waves

# THE OSI Layers - an Example (Sender)
- Example sending a POST request to an HTTPS webpage
- Layter 7 - Application
- - POST request with JSON data to HTTPS server
- Layer 6 - Presentation
- - Serialize JSON to flat byte strings
- Layer 5- Session
- - Request to establish TCP connection/TLS
- Layer 4 - Transport
- - Sends SYN re4quest target port 443
- Layer 3 - Network
- - SYN is placed an IP packet(s) and adds the source/dest IPs
- Layer 2 - Data link
- - Each packet goes into a single frame and adds the source/dest MAC addresses
- Layer 1 - Physical
- - Each frame becomes string of bits which converted into either a radio signal (wifi), electric signal (ethernet), or light (fiber)

# THE OSI Layers - an Example (Receiver)
- Receiver computer receives the POST request the other way around
- Layer 1 - Physical
- - Radio, electric or light is received and converted into digital bits
- Layer 2 - Data link
- - The bits from Layer 1 is assembled into frames
- Layer 3 - Network
- - The frames from layer 2 are assembled into IP packet
- Layer 4 - Transport
- - The IP packets from layer 3 are assembled into TCP segments
- - Deals with Congestion control/flow control/retransmission in case of TCP
- - If sement is SYN we don't need to go further into more layers as we are still processing the connection request
- Layer 5- Session
- - The connection session is established or identified
- - We only arrive at this layer when necessary (three way handshake is done)
- Layer 6 - Presentation
- - Deserialize flat byte strings back to JSON for the app to consume
- Layter 7 - Application
- - Application understands the JSON POST request and your express json or apache request receive event is triggered

# Switch & Router
## Switch
- Re-transmit the data
- Subnet
- Mostly looks for 2 Layer (Physical, Data Link)
## Router
- Acts like a switch but need IP Addresses
- Could have multiple routers

# Content Delivery Network (CDN)
## Client
## Layer 4 Proxy, Firewall
## Layer 7 Load Balancer/CDN
- Way slower than firewall if you want use cache (You go all the way to layer 7)
- Final destination to Client
## Server

# The shortcomings of the OSI Model
- OSI Model has too many layers which can be hard to comprehend
- Hard to argue about which layer does what
- Simpler to deal with Layers 5-6-7 as just one layer, application
- TCP/IP Model does just that

# TCP/IP Model
- Much simpler than OSI, just 4 layers
- Application (Layer 5, 6, and 7)
- Transport (Layer 4)
- Internet (Layer 3)
- Data link (Layer 2)
- Physical layer is not officially covered in the model



</details>
<!-- ##### END OF TOPIC: OSI MODEL ##### -->


<!-- ##### START OF TOPIC: INTERNET PROTOCOL ##### -->
<details>
<summary>Internet Protocol</summary>

# 1. The IP building blocks
- Understanding the IP Protocol

## IP Address
- Layer 3 property
- Can be set automatically or statically
- Network and Host portion
- 4 bytes in IPv4 - 32 bits

## Network vs Host
- a.b.c.d/x (a.b.c.d are integers) x is the network bits and remains are host
- Example 192.168.254.0/24
- The first 24 bits (3 bytes ) are network the rest 8 are for host
- This means we can have 2^24 (16777216) networks and each network has 2^8 (255) host
- Also called a subnet

## Subnet Mask
- 192.168.254.0/24 is also called a subnet
- The subnet has a mask 255.255.255.0
- Subnet mask is used to determine whatever an IP is in the same subnet

## Default Gateway
- Most networks consists of hosts and a Default Gateway
- When host A want to talk to B directly if both are in the same subnet
- Otherwise A sends it to someone who might know, the gateway
- The Gateway has an IP Address and each host should know its gateway

# 2. The IP Packet
- Anatomy of the IP Packet

# IP Packet
- The IP Packet has headers and data sections
- IP Packet header is 20 bytes (can go up to 60 bytes if options are enabled)
- Data section can go up to 65536 (Average is 1500 bytes)

# 3. ICMP

# ICMP
- Stands for Internet Control Message Protocol
- Designed for informationnal messages
- - Host unreachable, port unreachable, fragmentation needed
- - Packet expired (infinite loop in routers)
- Uses IP directly
- PING and traceroute use it
- Doesn't require listeners or ports to be opened
- Some firewalls block ICMP for security reasons
- That is why PING might not work in those cases
- Disabling ICMP also can cause real damage with connection establishment (TCP Blackhole)
- - Fragmentation needed
- PING demo

# Ping

# TraceRoute
- Can you identify the entire path your IP Packet takes?
- Clever use of TTL
- Increment TTL slowly and  you will get the router IP address for each hop
- Doesn't always work as path changes and ICMP might be blocked



</details>
<!-- ##### END OF TOPIC: INTERNET PROTOCOL ##### -->


<!-- ##### START OF TOPIC: UDP ##### -->
<details>
<summary>UDP</summary>

- User Datagram Protocol

# 1. UDP
- Stands for User Datagram Protocol
- Layer 4 protocol
- Ability to address processes in a host using ports
- Simple protocol to send and receive data
- Prior communication not required (double edge sword)
- Stateless no knowledge is stored on the host
- 8 byte header Datagram

# UDP Use cases
- Video streaming
- VPN
- DNS
- WebRTC

# Multiplexing and demultiplexing
- IP target hosts only
- Hosts run many apps each with different requirements
- Ports now identidy the "app" or "process"
- Sender multiplexes all its apps into UDP
- Receiver demultiplex UDP datagrams to each app

# 2. UDP Datagram
- The anatomy of the UDP datagram

# UDP Datagram
- UDP Header is 8 bytes only (IPv4)
- Datagram slides into an IP packet as "data"
- Port are 16 bit (0 to 65535)

# UDP Pros and Cons
## Pros
- Simple protocol
- Header size is small so datagrams are small
- Uses less bandwidth
- Stateless
- Consumes less memory (no state stored in the server/client)
- Low latency - no handshake, order, retransmission or guaranteed delivery

## Cons
- No acknowledgement
- No guarantee delivery
- Connection-less - anyone can send data without prior knowledge
- No Flow control
- No congestion control
- No ordered packets
- Security - can be easily spoofed

</details>
<!-- ##### END OF TOPIC: UDP ##### -->


<!-- ##### START OF TOPIC: TCP ##### -->
<details>
<summary>TCP</summary>

# 1. TCP
- Stands for Transmission Control Protocol
- Layer 4 protocol
- Ability to address processes in a host using ports
- "controls" the transmission unlike UDP which is a firehose
- Connection
- Requires handshake
- 20 bytes headers Segment (can go to 60)
- Stateful

# TCP Use cases
- Reliable communication
- Remote shell
- Database connections
- Web communications
- Any bidirectional communication

# TCP Connection
- Connection is a Layer 5 (session)
- Connection is an agreement between client and server
- Must create a connection to send data
- Connection is identified by 4 properties
- - SourceIP-SourcePort
- - DestinationIP-DestinationPort
- Can't send data outside of a connection
- Sometimes called socket or file descriptor
- Requires a 3-way TCP handshake
- Segments are sequenced and ordered
- Segments are acknowledged
- Lost segments are retransmitted

# Multiplexing and demultiplexing
- IP target hosts only
- Hosts run many apps each with different requirements
- Ports now identify the "app" or "process"
- Sender multiplexes all its apps into TCP connections
- Receiver demultiplex TCP segments to each app based on connection pairs

# 2. TCP Segment
- The anatomy of the TCP Segment

# TCP Segment
- TCP segment Header is 20 bytes and can go up to 60 bytes
- TCP segments slides into an IP packet as "data"
- Port are 16 bit (0 to 65535)
- Sequences, Acknowledgment, flow control and more

# Maximum Segment Size
- Segment Size depends the MTU of the network
- Usually 512 bytes can go up to 1460
- Default MTU in the Internet is 1500 (results in MSS 1460)
- Jumbo frames MTU goes to 9000 or more
- MSS can be larger in jumbo frames cases

</details>
<!-- ##### END OF TOPIC: TCP ##### -->


<!-- ##### START OF TOPIC:TLS ##### -->
<details>
<summary>TLS</summary>

- Transport Layer Security

# Why TLS
- We encrypt with symmetric key algorithms
- We need to exchange the symmetric key
- Key exchange uses asymmetric key (PKI)
- Authenticate the server
- Extensions (SNI, preshareed, 0RTT)

# TLS Summary
- Vanilla HTTP
- HTTPS
- TLS 1.2 Handshake (two round trips)
- Diffie Hellman
- TLS 1.3 Improvements (one round trip can be zero)

</details>
<!-- ##### END OF TOPIC:TLS ##### -->

<!-- ##### START OF TOPIC: HTTP/1.1 ##### -->
<details>
<summary>HTTP/1.1</summary>

# HTTPS
- Key exchange between server and client (synchronous for fast communication)

# HTTP 1.0
1. Client open connection
2. request connection
3. Client receive & close connection
4. Open connection so on
- New TCP connection with each request
- Slow
- Buffering (transfer-encoding:chunked didn't exist)
- No multi-homed websites (HOST header)

# HTTP 1.1
1. Client open connection
2. request files & keep connection alive
3. Client receives
4. request files and so on
5. Client receives so on
- Persisted TCP Connection
- Low Latency & Low CPU Usage
- Streaming with Chunked transfer
- Pipelining (disabled by default)
- Proxying & Multi-homed websites
- - 1 IP can holds multiple websites

# HTTP/2
- SPDY
- Compression
- Multiplexing
- Server Push
- Secure by default
- Protocol Negotiation during TLS (NPN/ALPN)

# HTTP over QUIC (HTTP/3)
- Replaces TCP with QUIC (UDP with Congestion control)
- All HTTP/2 features
- Without HOL

</details>
<!-- ##### END OF TOPIC: HTTP/1.1 ##### -->


<!-- ##### START OF TOPIC: WebSocket ##### -->
<details>
<summary>WebSocket</summary>

# WebSockets use cases
- Chatting
- Live Feed
- Multiplayer gaming
- Showing client progress/logging

# Websockets Pros and COns
## Pros
- Full-duplex (no polling)
- HTTP compatible
- Firewall friendly (standard)
## Cons
- Proxying is tricky
- L7 LB challenging (timeouts)
- Stateful, difficult to horizontally scale

# Do you have to use WebSockets?
- It's true that many web-based chat app plugins work well and provide a good user experience, even when using HTTP. However, these plugins typically use techniques to mitigate the latency issues associated with HTTP. For example:

1. Long Polling: Some chat app plugins use long polling, where the client sends a request to the server, and the server keeps the request open until new data is available. This technique can help reduce latency by allowing the server to respond immediately when new data is available.

2. Server-Sent Events (SSE): SSE is a server-side technology that allows the server to push new data to the client when it becomes available. This technique can help reduce latency by allowing the server to send data immediately when it is available, without waiting for the client to request it.

3. Polling with a low interval: Some chat app plugins use polling with a low interval, where the client sends a request to the server every few seconds to check for new data. While this technique can result in higher network traffic and battery drain, it can still provide a good user experience if the interval is set low enough.

- These techniques can help mitigate the latency issues associated with HTTP and provide a good user experience for chat app plugins. However, if low latency is critical for your chat app, WebSockets or other real-time communication protocols may still be a better choice.

</details>
<!-- ##### END OF TOPIC: WebSocket ##### -->

<!-- ##### START OF TOPIC: HTTP/2 ##### -->
<details>
<summary>HTTP/2</summary>

# HTTP/2 Pros
- Multiplexing over Single Connection (save resources)
- Compression (Headers & Data)
- Server Push
- Secure by default
- Protocol Negotiation during TLS (ALPN)

# HTTP/2 Cons
- TCP head of line blocking
- Server Push never picked up
- High CPU usage



</details>
<!-- ##### END OF TOPIC: HTTP/2 ##### -->


<!-- ##### START OF TOPIC: HTTP/3 ##### -->
<details>
<summary>HTTP/3</summary>

- HTTP over QUICK Multiplexed streams

# HTTP/2 Disadvantages
## TCP head of line blocking
- TCP segments must be delivered in order
- But streams don't have to
- Blocking requests

# HTTP/3 & QUIC (Solution to HTTP/2)
- HTTP/3 uses QUIC
- Like HTTP/2, QUIC has streams
- But QUIC use UDP instead
- Application decides the boundary

# HTTP/3 & QUIC Pros
- QUIC has many other benefits
- Merges Connection setup + TLS in one handshake
- Has congestion control at stream level
- Connection migration (connectionID)
- Why not HTTP/2 over QUIC?
- - Header compression algorithm

# HTTP/3 & QUIC Cons
- Takes a lot of CPU (parsing logic)
- UDP could be blocked
- IP Fragmentations is the enemy

</details>
<!-- ##### END OF TOPIC: HTTP/3 ##### -->

<!-- ##### START OF TOPIC: gRPC ##### -->
<details>
<summary>gRPC</summary>

- Taking HTTP/2 to the next level

# Client Server Communication Protocol
- SOAP, REST, GraphQL
- SSE, WebSockets
- Raw TCP

# The Problem with Client Libraries
- Any communication protocol needs client library for the language of choice
- - SOAP Library
- - HTTP Client Library
- Hard to maintain and patch client libraries
- - HTTP/1.1 HTTP/2, new features, security etc.

# Why gRPC was invented?
- Client Library: One library for popular languages
- Protocol: HTTP/2 (hidden implementation)
- Message Format: Protocol buffers as format

# gRPC modes
## Unary RPC
- request/response
## Server streaming RPC
- server streaming (ex: downloading content from server)
## Client streaming RPC
- client streaming (ex: uploading content to the server)
## Bidirectional streaming RPC
- Both server and client

# gRPC Pros & Cons
## Pros
- Fast & Compact
- One Client Library
- Progress Feedback (upload)
- Cancel Request (H2)
- H2/Protobuf
## Cons
- Schema
- Thick Client
- Proxies
- Error handling
- No native browser support
- Timeouts (pub/sub)

# Can I write my own protocol too?
- Yes, you can, Spotify did (Hermes) but guess what
- Only you will be using it so...
- Spotify moved to gRPC not because of limitation of Hermes but because they are isolated.


</details>
<!-- ##### END OF TOPIC: gRPC ##### -->


<!-- ##### START OF TOPIC: WebRTC ##### -->
<details>
<summary>TEMP</summary>

- Web Real-Time Communication

# WebRTC Overview
- Stands for Web Real-Time Communication
- Find a peer to peer path to exchange video and audio in an efficient and low latency manner
- Standardized API
- Enables rich communications browsers, mobile, IOT devices

# WebRTC Demystified
- NAT
- STUN, TURN
- ICE
- SDP
- Signaling the SDP

# Network Address Translation (NAT)
## NAT Translations Method
# One to One NAT (Full-cone NAT)
- Packets to external IP:port on the router always maps to internal IP:port without exceptions
# Address restricted NAT
- Packets to external IP: port on the router always maps to internal IP:port as long as source address from packet matches the table (regardless of port)
- Allow if we communicated with this host before
# Port restricted NAT
- Packets to external IP:port on the router always maps to internal IP:port as long as source address and port from packet matches the table
- Allow if we communicated with this host:port before
# Symmetric NAT (Uncommon)
- Paackets to external IP:port on the router always maps to internal IP:port as long as source address and port from packet matches the table
- Only Allow if the full pair match

# Session Traversal Utilities for NAT (STUN)
- Tell me my public ip address/port through NAT
- Works for Full-cone, Port/Address restricted NAT
- Doesn't work for symmetric NAT
- STUN server port 3478, 5349 for TLS
- Cheap to maintain

# Traversal Using Relays around NAT (TURN)
- In case of Symmetric NAT we use TURN
- It's just a server that relays packets
- TURN default server port 3478, 5349 for TLS
- Expensive to maintain and run

# Interactive Connectivity Establishment (ICE)
- ICE collects all available candidates (local IP addresses, reflexive addresses - STUN ones and relayed addresses - TURN ones)
- Called ice candidates
- All the collected addresses are then sent to the remote peer via SDP

# Session Description Protocol (SDP)
- A format that describes ice candidates, networking options, media options, security options and other stuff
- Not really a protocol its a format
- Most important concept in WebRTC
- The goal is to take the SDP generated by a user and send it "somehow" to the other party

# Signaling
- SDP Signaling
- Send the SDP that we just generated somehow to the other party we wish to communicate with
- Signaling can be done via a tweet, QR code, Whatsapp, WebSockets, HTTP request DOESN'T MATTER! Just get that large string to the other party

# DEMO

# WebRTC Pros & Cons
## Pros
- P2P is great! low latency for high bandwidth content
- Standardized API I don't have to build my own
## Cons
- Maintaining STUN & TURN servers
- Peer 2 Peer falls apart in case of multiple participants (discord case)

# Media API
- getUserMedia to access microphone, video camera
- RTCPConnection.addTrack(stream)
- https://web.dev/webrtc-basics/

# onIceCandidate and addIceCandidate
- To maintain the connection nas new candidates come and go
- onIceCandidate tells user there is a new c andidate after the SDP has already been created
- The candidate is signaled and sent to the other party
- The other party uses addiceCandidate to add it to its SDP

# Create your own STUN & TURN server
- COTURN open source project
- https://github.com/coturn/coturn

# Public STUN servers
- stun1.1.google.com:19302
- stun2.1.google.com:19302
- stun3.1.google.com:19302
- stun4.1.google.com:19302
- stun.stunprotocol.org:3478
</details>
<!-- ##### END OF TOPIC: WebRTC ##### -->



</details>
<!-- ########## END OF CHAPTER: 003 ########## -->




<!-- ########## START OF CHAPTER: 004 ########## -->
<details>
<summary>004. Many ways to HTTPS</summary>

<!-- ##### START OF TOPIC: HTTPS over TCP with TLS 1.2 ##### -->
<details>
<summary>HTTPS over TCP</summary>

# HTTPS over TCP with TLS 1.2

# HTTPS over TCP with TLS 1.3
- Exchange Algorithm
- Symmetric Key
- 1 less roundtrip compared to TLS 1.2
- Alaways use TLS 1.3 except for compatibility reason

# HTTPS over QUIC
- HTTP/3
- 3-way handshake for tcp & TLS handshake happens in the same roundtrip
- Technically UDP, but looks like stateful connection

# HTTPS over TCP Fast Open with TLS 1.3 (Theory)
- Not secured
- Just for fun

# HTTPS over TCP with TLS 1.3 0-Roundtrip
- Pre-shared key

# HTTPS over QUIC 0-Roundtrip
- Pre-shared key



</details>
<!-- ##### END OF TOPIC: HTTPS over TCP with TLS 1.2 ##### -->


</details>
<!-- ########## END OF CHAPTER: 004 ########## -->




<!-- ########## START OF CHAPTER: 005 ########## -->
<details>
<summary>005 - Backend Execution Patterns</summary>


<!-- ##### START OF TOPIC: Process vs Thread ##### -->
<details>
<summary>Process vs. Thread</summary>

# What is a Process?
- A set of instructions
- Has an isolated memory
- Has a Process Identifier (PID)
- Scheduled in the CPU

# What is a Thread?
- Light Weight Process (LWP)
- A set of instructions
- Shares memory with parent process
- Has a ID
- Scheduled in the CPU

# Single Threaded Process
- One Process with a single thread
- Simple
- Examples NodeJS

# Multi-Processes
- App has multiple processes
- Each has its own Memory
- Examples NGINX/Postgres
- Take advantage of multi-cores
- More memory but isolated (Compared to multi-threaded)
- - Each process has its own memory (Memory Fork)
- Redis backup routine (COW)

# Multi-Threaded
- One Process, multiple threads
- Shared Memory (compete)
- Take advantage of multi-cores
- Require less memory (Compared to Multi-Processes)
- Race conditions
- Locks and Latches (SQL Server)
- Examples Apache, Envoy

# How many is too many?
- Too many processes/threads
- CPU context switch
- Multiple Cores help
- Rule of thumb -> # Cores = # Processes

</details>
<!-- ##### END OF TOPIC: Process vs Thread ##### -->


<!-- ##### START OF TOPIC: How the Backend Accepts Connections ##### -->
<details>
<summary>How the Backend Accepts Connections</summary>

# Connection Establishment
- TCP Three way handshake
- SYN/SYN-ACK/ACK
- But what happens on the backend?

## Zoom-in Server
- Server Listens on an address:port
- Client connects
- Kernel does the handshake creating a connection
- Backend process "Accepts" the connection

## Zoom-in little bit futher (Entire life cycle)
- Kernel creates a socket & two queues SYN and Accept
- Client sends a SYN
- Kernels adds to SYN queue, replies with SYN/ACK
- Client replies with ACK
- Kernel finish the connection
- Kernel adds full connection to Accept queue
- Backend accepts a connection, removed from accept queue
- A file descriptor for the connection (Uniquely identifies the connection)

# Problem with accepting connections
- Backend doesn't accept fast enough
- Clients who don't ACK (ex: SYN flood attack)
- Small backlog

</details>
<!-- ##### END OF TOPIC: How the Backend Accepts Connections ##### -->


<!-- ##### START OF TOPIC: Reading and Sending Data ##### -->
<details>
<summary>Reading and Sending Data</summary>

# Send and receive buffers
- Client sends data on a connection
- Kernel puts data in receive queue
- Kernel ACKs (may delay) and update window
- App calls read to copy data (Copying is expensive!)


</details>
<!-- ##### END OF TOPIC: Reading and Sending Data ##### -->


<!-- ##### START OF TOPIC: The Listener, The Accepter and the Reader ##### -->
<details>
<summary>The Listener, The Accepter and the Reader</summary>

# Single Listener/Single Worker Thread
## node.js
- Single Thread

# Single Listener/Multiple Worker threads
## Memcached
- Multiple threads with single acceptor

# Single Listener/Multiple Worker threads with load balancing
## RAMCloud

# Multiple Threads single Socket
## Nginx
- Multiple threads with multiple acceptors

# Multiple Listeners on the same port
## Nginx, Envoy
- Multiple threads with socket sharding (SO_REUSEPORT)


</details>
<!-- ##### END OF TOPIC: The Listener, The Accepter and the Reader  ##### -->


<!-- ##### START OF TOPIC: Idempotency ##### -->
<details>
<summary>Idempotency</summary>

- Resending the Request without affecting backend

# What is idempotency?
- API /postcomment
- Takes comment and appends it to table
- What if the user/proxy retries it?
- Very bad for financial systems
- Idempotent request can be retried without affecting backend
- Easy implementation send a requestId
- Also known as idempotency token

# In HTTP
- GET is idempotent
- POST isn't, but we can make it
- Browsers and proxies treat GET as idempotent
- Make sure your GETs are idempotent


</details>
<!-- ##### END OF TOPIC: Idempotency ##### -->


<!-- ##### START OF TOPIC: Nagle's algorithm ##### -->
<details>
<summary>Nagle's algorithm</summary>

# Nagle's algorithm
- In the telnet days sending a single byte in a segment is a waste
- Combine small segments and send them in a single one
- The client can wait for a full MSS before sending the segment
- No wasted 40 bytes header (IP + TCP) for few bytes of data

# Problem with Nagle's algorithm
- Sending large data causes delay

# Disabling Nagle's algorithm
- Most clients today disable Nagle's algorithm
- I rather get performance than small bandwidth
- TCP_NODELAY
- Curl disabled this back in 2016 by default because TLS handshake was slowed down

</details>
<!-- ##### END OF TOPIC: Nagle's algorithm  ##### -->



</details>
<!-- ########## END OF CHAPTER: 005 ########## -->


<!-- ########## START OF CHAPTER: 006 ########## -->
<details> <!-- OBJECTIVE -->
<summary>006 - Proxying and Load Balancing</summary>

<!-- ##### START OF TOPIC: Proxy vs. Reverse Proxy ##### -->
<details>
<summary>Proxy vs. Reverse Proxy</summary>

# Proxy vs. Reverse Proxy
## Proxy
- I want to go to google.com through proxy: my-proxy.com
- my-proxy.com
- Google says "I just know that I received a request from my-proxy"

### Proxy Use Cases
- Caching
- Anonymity
- Logging
- Block Sites
- Microservices

## Reverse Proxy
- I want to go google.com
- google.com (Frontend server or Edge server )
- google-server1, google-server2 (Client doesn't know about backend server)

### Reverse Proxy Use Cases
- Caching
- Load Balancing
- Ingress
- Canary Deployment
- Microservices

</details>
<!-- ##### END OF TOPIC: Proxy vs. Reverse Proxy ##### -->

<!-- ##### START OF TOPIC: Layer 4 vs. Layer 7 Load Balancers ##### -->
<details>
<summary>Layer 4 vs. Layer 7 Load Balancers</summary>

# Load Balancer (fault tolerant)
- Load Balancer is reverse proxy

## Layer 4 Load Balancer
- TCP Connection between Client and Load Balancer
- TCP Connection between Load Balancer and backend server

### Layer 4 Load Balancer (Pros and Cons)
#### Pros
- Simpler load balancing
- Efficient (no data lookup)
- More secure
- Works with any protocol
- One TCP connection (NAT)

#### Cons
- No smart load balancing
- NA microservices
- Sticky per connection
- No caching
- Protocol unaware (can be dangerous) bypass rules

## Layer 7 Load Balancer
- Same as Layer 4 Load Balancer
- When a client connects to the L7 load balancer, it becomes protocol specific.
- Any logical "request" will be forwarded to a new backend server.
- This could be one or more segments

### Layer 7 Load Balancer (Pros and Cons)
#### Pros
- Smart load balancing
- Caching
- Great for microservices
- API Gateway logic
- Authentication

#### Cons
- Expensive (looks at data)
- Decrypts (terminates TLS)
- Two TCP Connections
- Must share TLS certificate
- Needs to buffer
- Needs to understand protocol

</details>
<!-- ##### END OF TOPIC: Layer 4 vs. Layer 7 Load Balancers ##### -->


</details>
<!-- ########## END OF CHAPTER: 006 ########## -->


<!-- ########## START OF CHAPTER: Extra ########## -->
<details> <!-- OBJECTIVE -->
<summary>Extra</summary>


<!-- ##### START OF TOPIC: How ChatGPT uses Server Sent Events ##### -->
<details>
<summary>How ChatGPT uses Server Sent Events</summary>

- ??

</details>
<!-- ##### END OF TOPIC: How ChatGPT uses Server Sent Events ##### -->

</details>
<!-- ########## END OF CHAPTER: Extra ########## -->



<!-- ##### START OF TOPIC: TEMP ##### -->
<details>
<summary>TEMP</summary>

- Content

</details>
<!-- ##### END OF TOPIC: TEMP ##### -->

# Resources
- [This](https://www.udemy.com/course/fundamentals-of-backend-communications-and-protocols/)
- [Intro to QUIC](https://youtu.be/EkVd4k0R4Tw)
- [Idempotency]
- [Nagle's algorithm]

