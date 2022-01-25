import json


class User:
    """class to manage user information"""
    managerPassword = "xyz"

    def __init__(self, username) -> None:
        self.username = username
        self.role = "guest"
        self.store = {}

    def getValue(self, key) -> str:
        if key in self.store:
            return self.store[key]
        else:
            return "undefined"

    def setValue(self, key, value) -> None:
        self.store[key] = value

    def upgrade(self, password) -> bool:
        if (password == User.managerPassword):
            self.role = "manager"
            return True
        else:
            return False

    def downgrade(self) -> None:
        self.role = "guest"

    def __str__(self) -> str:
        userDetails = "\nName: " + self.username
        userDetails += "\nRole: " + self.role
        userDetails += "\nStore: " + json.dumps(self.store)
        return userDetails
