const mongoose = require("mongoose");
const { userSchema } = require("./user");
const { messageSchema } = require("./message");
const Joi = require("joi");

const channelSchema = new mongoose.Schema({
  users: [{ type: mongoose.Schema.Types.ObjectId, ref: "user" }],
  type: {
    type: String,
    enum: ["private", "group"],
    required: true,
  },
  messages: [messageSchema],
  addedOn: {
    type: Date,
    default: Date.now,
  },
});

const Channel = mongoose.model("channel", channelSchema);

function validateChannel(channel) {
  const schema = Joi.object({
    users: Joi.array().items(Joi.string().email()).required(),
    type: Joi.string().valid("private", "group").required(),
  });

  return schema.validate(channel);
}

exports.Channel = Channel;
exports.validate = validateChannel;
exports.channelSchema = channelSchema;
