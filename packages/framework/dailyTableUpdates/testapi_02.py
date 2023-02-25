import requests
import json
import githubkeys

repo_name = "trilinos/Trilinos"
repo_owner = "trilinos"

filter_params = "is:pr merged:2023-02-22T12:00:00-07:00..2023-02-23T12:00:00-07:00 base:develop"

url = f"https://api.github.com/search/issues?q=repo:{repo_owner}/{repo_name}+{filter_params}"
api_key = githubkeys.api_key

headers = {
    "Authorization": f"Bearer {api_key}"
}

response = requests.get(url, headers=headers)
data = json.loads(response.text)

count = 1
for issue in data["items"]:
    if "pull_request" in issue:
        print(f"#{issue['number']}: {issue['title']} counteer = {count}")
        count += 1 
