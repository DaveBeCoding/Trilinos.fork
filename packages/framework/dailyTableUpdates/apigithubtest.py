import requests
import json
import keys

url = "https://api.github.com/repos/trilinos/Trilinos/pulls?q=is%3Apr+merged%3A2023-02-22T12%3A00%3A00-07%3A00..2023-02-23T12%3A00%3A00-07%3A00+base%3Adevelop"

# Set the API key

# Set the headers with the API key
headers = {
    "Authorization": f"Bearer {keys.api_key}"
}

# Make the request with the headers
response = requests.get(url, headers=headers)

print(f"Response status code: {response.status_code}")

data = json.loads(response.text)

print(json.dumps(data, indent=4))

for pr in data:
    print(f"PR #{pr['number']} state: {pr['state']}")
    if pr["state"] == "closed":
        print(f"#{pr['number']}: {pr['title']}")
