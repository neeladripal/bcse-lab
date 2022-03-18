import React from "react";

function Search(props) {
  const { searchString, onSearchChange } = props;

  return (
    <div className="search-box">
      <div className="input-wrapper">
        <img
          src={process.env.PUBLIC_URL + "search-icon.svg"}
          alt=""
          className="search-icon"
        />
        <input
          type="text"
          className="input-text"
          value={searchString}
          onChange={(e) => {
            onSearchChange(e.target.value);
          }}
          placeholder="Search by name or email"
        />
      </div>
    </div>
  );
}

export default Search;
