const express = require("express");
const { User, validate } = require("../models/user");
const router = express.Router();
const _ = require("lodash");
const bcrypt = require("bcrypt");
const auth = require("../middleware/auth");

// get the current user
router.get("/me", auth, async (req, res) => {
  const user = await User.findById(req.user._id).select(
    "name email profilePic"
  );
  res.send(user);
});

// search an array of users
router.get("/", auth, async (req, res) => {
  const userIds = req.body.userIds;
  console.log(userIds);
  const users = await User.find({ _id: userIds }).select(
    "name email profilePic"
  );
  res.send(users);
});

// search a user
router.get("/search", auth, async (req, res) => {
  if (!req.query.key)
    return res.status(400).send("Search value must not be empty");

  const key = new RegExp("^" + req.query.key, "i");
  const users = await User.find({
    $or: [{ name: key }, { email: key }],
  })
    .find({ _id: { $ne: req.user._id } })
    .limit(20)
    .select({ name: 1, email: 1, profilePic: 1 });
  res.send(users);
});

// register a new user
router.post("/", async (req, res) => {
  const { error } = validate(req.body);
  if (error) return res.status(400).send(error.details[0].message);

  let user = await User.findOne({ email: req.body.email });
  if (user) return res.status(400).send("User already registered");

  user = new User(_.pick(req.body, ["name", "email", "password"]));

  // generate the salt, salt is a part of the hashed password as well
  const salt = await bcrypt.genSalt(10);
  user.password = await bcrypt.hash(user.password, salt);

  await user.save();

  const token = user.generateAuthToken();
  // custom headers must precede with an x
  res
    .header("x-auth-token", token)
    .header("access-control-expose-headers", "x-auth-token")
    .send(_.pick(user, ["name", "profilePic"]));
});

module.exports = router;
