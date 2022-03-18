const _ = require("lodash");
const { Channel } = require("../models/channel");
const { Message, validate } = require("../models/message");

module.exports = function (server) {
  const io = require("socket.io")(server, {
    cors: {
      origin: process.env.CLIENT_URI,
    },
  });

  io.use((socket, next) => {
    const userId = socket.handshake.auth.userId;
    if (!userId) {
      return next(new Error("Invalid userId"));
    }
    socket.userId = userId;
    next();
  });

  io.on("connection", (socket) => {
    socket.join(socket.userId);

    socket.on("global_message", async ({ body }, callback) => {
      // check the request body for errors
      const { error } = validate(body);
      if (error) return callback(error.details[0].message);

      const message = new Message({
        sender: socket.userId,
        type: body.type,
        content: body.content,
      });

      await message.save();

      const newMessage = {
        _id: message._id,
        sender: { _id: message.sender, name: body.senderName },
        type: message.type,
        content: message.content,
        addedOn: message.addedOn,
      };

      io.emit("global_message", {
        body: newMessage,
        from: "global",
      });
    });

    socket.on("private_message", async ({ body }, callback) => {
      // check the request body for errors
      const { error } = validate(body);
      if (error) return callback(error.details[0].message);

      let channel = await Channel.findById(body.channelId);

      const senderId = socket.userId;
      const receiverId = channel.users
        .filter((userId) => userId != senderId)[0]
        .toString();

      if (!channel.users.includes(senderId))
        return callback("Attempt to access unauthorized channel");

      const message = new Message({
        sender: socket.userId,
        type: body.type,
        content: body.content,
      });

      channel.messages.push(message);
      await channel.save();

      const newMessage = {
        _id: message._id,
        sender: { _id: message.sender, name: body.senderName },
        type: message.type,
        content: message.content,
        addedOn: message.addedOn,
      };

      io.to(receiverId).to(senderId).emit("private_message", {
        body: newMessage,
        from: channel._id,
      });
    });
  });
};
