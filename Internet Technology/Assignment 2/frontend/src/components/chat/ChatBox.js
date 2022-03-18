import React, { useState } from "react";
import Picker from "emoji-picker-react";
import FilePond from "../common/FilePond";

function ChatBox(props) {
  const { onMessageSend } = props;
  const [messageText, setMessageText] = useState("");
  const [pickerVisible, togglePicker] = useState(false);
  const [images, setImages] = useState([]);
  const [pondVisible, togglePond] = useState(false);

  const onEmojiClick = (event, emojiObject) => {
    setMessageText(messageText + " " + emojiObject.emoji);
    togglePicker(false);
  };

  const handleEmojiIconClick = (e) => {
    if (pondVisible) togglePond(false);
    togglePicker(!pickerVisible);
  };

  const handleImageIconClick = (e) => {
    setMessageText("");
    if (pickerVisible) togglePicker(false);
    if (pondVisible && images.length > 0) setImages([]);
    togglePond(!pondVisible);
  };

  const handleMessageTextChange = (e) => {
    setMessageText(e.target.value);
  };

  const convertToBase64 = (file) => {
    return new Promise((resolve, reject) => {
      const fileReader = new FileReader();
      fileReader.readAsDataURL(file);
      fileReader.onload = () => {
        resolve(fileReader.result);
      };

      fileReader.onerror = (err) => {
        reject(err);
      };
    });
  };

  const handleMessageSend = async (e) => {
    e.preventDefault();
    if (images.length > 0) {
      console.log(images);
      const file = images[0].file;
      const base64 = await convertToBase64(file);
      const message = {
        type: "image",
        content: base64,
      };
      setImages([]);
      if (pondVisible) togglePond(false);
      onMessageSend(message);
    }
    if (messageText !== "") {
      const message = {
        type: "text",
        content: messageText,
      };
      setMessageText("");
      onMessageSend(message);
    }
  };

  return (
    <div>
      <form className="chat-box" onSubmit={handleMessageSend}>
        {pickerVisible && (
          <Picker
            pickerStyle={{ position: "absolute", bottom: "70px" }}
            onEmojiClick={onEmojiClick}
          />
        )}
        {pondVisible && (
          <div className="image-pond">
            <FilePond
              files={images}
              onupdatefiles={setImages}
              credits={false}
              name="image"
              labelIdle='Drag & Drop your image or <span class="filepond--label-action">Browse</span>'
              acceptedFileTypes={["image/*"]}
              maxFileSize={process.env.REACT_APP_IMAGE_SIZE}
              imageTransformOutputQuality={
                process.env.REACT_APP_IMAGE_TRANSFORM_QUALITY
              }
            />
          </div>
        )}
        <div className="input-wrapper">
          <img
            src={process.env.PUBLIC_URL + "data.svg"}
            alt=""
            onClick={handleEmojiIconClick}
            className="icon in-chat-box"
          ></img>
          <img
            src={process.env.PUBLIC_URL + "image.svg"}
            alt=""
            onClick={handleImageIconClick}
            className="icon in-chat-box"
          ></img>
          <input
            type="text"
            placeholder={
              images.length > 0
                ? "Caption feature coming soon"
                : "Type a message"
            }
            onChange={handleMessageTextChange}
            value={messageText}
            className="input-text"
            disabled={images.length > 0 ? true : false}
          />
        </div>
        <input
          type="image"
          src={process.env.PUBLIC_URL + "send-icon.svg"}
          alt=""
          className="icon"
        />
      </form>
    </div>
  );
}

export default ChatBox;
