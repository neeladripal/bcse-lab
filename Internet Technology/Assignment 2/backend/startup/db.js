const mongoose = require("mongoose");
const logger = require("../startup/logging");

module.exports = function () {
  const db = process.env.MONGO_URI;
  mongoose.connect(db).then(() => logger.info("Connected to MongoDB..."));
};
