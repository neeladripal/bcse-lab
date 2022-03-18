const express = require("express");
const router = express.Router();
const _ = require("lodash");
const { Channel, validate } = require("../models/channel");
const { User } = require("../models/user");
const auth = require("../middleware/auth");

// get all the channels
router.get("/", auth, async (req, res) => {
  let channels = await Channel.find({ users: req.user._id })
    .populate("users", "name email profilePic")
    .populate("messages.sender", "name")
    .select("users messages type");
  channels = channels.map((channel) => {
    channel.users = channel.users.filter((user) => user._id != req.user._id);
    return channel;
  });
  res.send(channels);
});

router.get("/:id", auth, async (req, res) => {
  const channel = await Channel.findById(req.params.id)
    .populate("users", "name email profilePic")
    .populate("messages.sender", "name")
    .select("users messages type");
  if (!channel) return res.status(400).send("Channel does not exist");
  channel.users = channel.users.filter((user) => user._id != req.user._id);
  res.send(channel);
});

// create a private channel
router.post("/private", auth, async (req, res) => {
  const { error } = validate(req.body);
  if (error) return res.status(400).send(error.details[0].message);

  const { users } = req.body;
  const sender = req.user;

  if (users.length !== 2) return res.status(400).send("2 users expected.");

  if (users[0] === users[1])
    return res.status(400).send("Users cannot be same.");

  if (users[0] !== sender.email) res.status(403).send("Access denied");

  const receiver = await User.findOne({ email: req.body.users[1] });
  if (!receiver) return res.status(400).send("Receiver not found.");

  let channel = await Channel.findOne({
    $and: [
      { users: { $elemMatch: { $eq: sender._id } } },
      { users: { $elemMatch: { $eq: receiver._id } } },
    ],
    type: "private",
  });
  if (channel) return res.status(400).send("Channel already exists");

  channel = new Channel({ users: [sender._id, receiver._id], type: "private" });
  await channel.save();

  res.send(_.pick(channel, ["_id", "users", "type"]));
});

module.exports = router;
