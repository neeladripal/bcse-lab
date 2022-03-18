const _ = require("lodash");
const express = require("express");
const router = express.Router();
const auth = require("../middleware/auth");
const { Channel } = require("../models/channel");
const { Message, validate } = require("../models/message");

// get global messages
router.get("/global", auth, async (req, res) => {
  const globalMessages = await Message.find().populate("sender", "id name");
  res.send(globalMessages);
});

//send global message
router.post("/global", auth, async (req, res) => {
  // check the request body for errors
  const { error } = validate(req.body);
  if (error) return res.status(400).send(error.details[0].message);

  const message = new Message({
    sender: req.user._id,
    type: req.body.type,
    content: req.body.content,
  });

  await message.save();

  const newMessage = {
    _id: message._id,
    sender: { _id: message.sender, name: req.body.senderName },
    type: message.type,
    content: message.content,
    addedOn: message.addedOn,
  };

  res.send(newMessage);
});

// post a message
router.post("/private", auth, async (req, res) => {
  // check the request body for errors
  const { error } = validate(req.body);
  if (error) return res.status(400).send(error.details[0].message);

  let channel = await Channel.findById(req.body.channelId);

  if (!channel.users.includes(req.user._id))
    return res.status(403).send("Attempt to access unauthorized channel");

  const message = new Message({
    sender: req.user._id,
    type: req.body.type,
    content: req.body.content,
  });

  channel.messages.push(message);
  await channel.save();

  const newMessage = {
    _id: message._id,
    sender: { _id: message.sender, name: req.body.senderName },
    type: message.type,
    content: message.content,
    addedOn: message.addedOn,
  };

  res.send(newMessage);
});

module.exports = router;
