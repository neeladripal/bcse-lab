const Joi = require("joi");
const mongoose = require("mongoose");

const messageSchema = new mongoose.Schema({
  sender: {
    type: mongoose.Schema.Types.ObjectId,
    ref: "user",
    required: true,
  },
  type: {
    type: String,
    required: true,
    enum: ["text", "image"],
    lowercase: true,
    trim: true,
  },
  content: {
    type: String,
    required: true,
  },
  addedOn: {
    type: Date,
    default: Date.now,
    required: true,
  },
});

const Message = mongoose.model("message", messageSchema);

function validateMessage(message) {
  const schema = Joi.object({
    channelId: Joi.alternatives()
      .try(Joi.objectId(), Joi.string().valid("global"))
      .required(),
    senderName: Joi.string().min(1).max(255).required(),
    type: Joi.string().valid("text", "image").required(),
    content: Joi.string().min(1).required(),
  });

  return schema.validate(message);
}

exports.Message = Message;
exports.validate = validateMessage;
exports.messageSchema = messageSchema;
