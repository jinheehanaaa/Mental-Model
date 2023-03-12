


<details> <!-- OBJECTIVE -->
<summary>Objective</summary>

- Learn Backend Engineering

</details>

<!-- ########## START of 002 ########## -->
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
<summary>TEMP</summary>

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
<!-- ########## END of 002 ########## -->



<!-- ########## START of 003 ########## -->
<details>
<summary>002 - Backend Communication Design Patterns</summary>

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


<!-- ##### START OF TOPIC: ##### -->
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
<!-- ##### END OF TOPIC: ##### -->




</details>
<!-- ########## END of 003 ########## -->


<!-- ##### START OF TOPIC: ##### -->
<details>
<summary>TEMP</summary>

- Content

</details>
<!-- ##### END OF TOPIC: ##### -->


</details>

<!-- ########## END OF 002 ########## -->


# Resources
- https://www.udemy.com/course/fundamentals-of-backend-communications-and-protocols/

