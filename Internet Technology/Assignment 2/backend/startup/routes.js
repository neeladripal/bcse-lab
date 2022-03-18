const express = require("express");
const users = require("../controllers/users");
const channels = require("../controllers/channels");
const messages = require("../controllers/messages");
const auth = require("../controllers/auth");
const error = require("../middleware/error");

module.exports = function (app) {
  // parse json objects from request body
  app.use(express.json());
  app.use(express.urlencoded({ extended: true }));
  app.use("/api/users", users);
  app.use("/api/channels", channels);
  app.use("/api/messages", messages);
  app.use("/api/auth", auth);
  app.use(error);
};
