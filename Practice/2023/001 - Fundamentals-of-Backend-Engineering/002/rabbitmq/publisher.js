/* RabbitMQ */
const amqp = require("amqplib");

const msg = {number: process.argv[2]}
connect();
async function connect() {
amqps://flybfnbb:HKTKVzhBxc3vzMN1GEm_IbOgIe5A3CDi@gull.rmq.cloudamqp.com/flybfnbb
    try {
        const amqpServer = "amqps://flybfnbb:HKTKVzhBxc3vzMN1GEm_IbOgIe5A3CDi@gull.rmq.cloudamqp.com/flybfnbb"
        //const amqpServer = "amqp://localhost:5672"
        const connection = await amqp.connect(amqpServer)
        const channel = await connection.createChannel();
        await channel.assertQueue("jobs");
        await channel.sendToQueue("jobs", Buffer.from(JSON.stringify(msg)))
        console.log(`Job sent successfully ${msg.number}`);
        await channel.close();
        await connection.close();
    }
    catch (ex){
        console.error(ex)
    }

}

// npm init -y
// node publisher.js 107