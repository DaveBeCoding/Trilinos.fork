import requests
import json
import githubkeys

url = "https://api.github.com/repos/trilinos/Trilinos/pulls?q=is%3Apr+merged%3A2023-02-22T12%3A00%3A00-07%3A00..2023-02-23T12%3A00%3A00-07%3A00+base%3Adevelop"

headers = {
    "Authorization": f"Bearer {githubkeys.api_key}"
}

response = requests.get(url, headers=headers)

print(f"Response status code: {response.status_code}")

data = json.loads(response.text)

print(json.dumps(data, indent=4))

for pr in data:
    print(f"PR #{pr['number']} state: {pr['state']}")
    if pr["state"] == "closed":
        print(f"#{pr['number']}: {pr['title']}")
