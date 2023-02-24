'''

This is a GitHub pull request SCraper script.

'''

'''Error out on NONE for Pull Request'''
# import requests
# from bs4 import BeautifulSoup

# # URL of the page to scrape
# url = "https://github.com/trilinos/Trilinos/pulls?q=is%3Apr+merged%3A2023-02-20T12%3A00%3A00-07%3A00..2023-02-21T12%3A00%3A00-07%3A00+base%3Adevelop"

# # Send a GET request to the URL and get the HTML content
# response = requests.get(url)
# html_content = response.content

# # Parse the HTML content using BeautifulSoup
# soup = BeautifulSoup(html_content, "html.parser")

# # Find the HTML element that contains the number of open pull requests
# open_prs_element = soup.find("a", {"data-selected-links": "repo_pulls"})
# open_prs_text = open_prs_element.text

# # Extract the number of open pull requests from the text
# open_prs = int(open_prs_text.strip().replace(",", ""))

# # Print the number of open pull requests
# print(f"Number of open pull requests: {open_prs}")

''' runs but can not find the number of open pull requests'''
# import requests
# from bs4 import BeautifulSoup

# # URL of the page to scrape
# url = "https://github.com/trilinos/Trilinos/pulls?q=is%3Apr+merged%3A2023-02-21T12%3A00%3A00-07%3A00..2023-02-22T12%3A00%3A00-07%3A00+base%3Adevelop+"

# # Send a GET request to the URL and get the HTML content
# response = requests.get(url)
# html_content = response.content

# # Parse the HTML content using BeautifulSoup
# soup = BeautifulSoup(html_content, "html.parser")

# # Find the HTML element that contains the number of open pull requests
# open_prs_element = soup.find("a", {"data-selected-links": "repo_pulls"})

# # If the element is found, extract the number of open pull requests from the text
# if open_prs_element is not None:
#     open_prs_text = open_prs_element.text
#     open_prs = int(open_prs_text.strip().replace(",", ""))
#     print(f"Number of open pull requests: {open_prs}")
# else:
#     print("Error: Could not find element containing number of open pull requests")

'''This was for open pull requests'''
# import requests
# from bs4 import BeautifulSoup

# # URL of the page to scrape
# url = "https://github.com/trilinos/Trilinos/pulls?q=is%3Apr+merged%3A2023-02-21T12%3A00%3A00-07%3A00..2023-02-22T12%3A00%3A00-07%3A00+base%3Adevelop+"

# # Send a GET request to the URL and get the HTML content
# response = requests.get(url)
# html_content = response.content

# # Parse the HTML content using BeautifulSoup
# soup = BeautifulSoup(html_content, "html.parser")

# # Find the HTML element that contains the number of open pull requests
# open_prs_element = soup.find("a", {"class": "UnderlineNav-item selected", "data-hotkey": "g p"})

# # If the element is found, extract the number of open pull requests from the text
# if open_prs_element is not None:
#     open_prs_text = open_prs_element.find("span", {"class": "Counter"}).text
#     open_prs = int(open_prs_text.strip().replace(",", ""))
#     print(f"Number of open pull requests: {open_prs}")
# else:
#     print("Error: Could not find element containing number of open pull requests")

'''Closed pull requests'''
# import requests
# from bs4 import BeautifulSoup

# url = 'https://github.com/trilinos/Trilinos/pulls?q=is%3Apr+merged%3A2023-02-21T12%3A00%3A00-07%3A00..2023-02-22T12%3A00%3A00-07%3A00+base%3Adevelop+'

# # Send a GET request to the URL
# response = requests.get(url)

# # Create a BeautifulSoup object to parse the HTML content
# soup = BeautifulSoup(response.content, 'html.parser')

# # Find the element containing the number of closed pull requests
# closed_count_element = soup.find('a', {'href': '?q=is%3Apr+is%3Aclosed+merged%3A2023-02-21T12%3A00%3A00-07%3A00..2023-02-22T12%3A00%3A00-07%3A00+base%3Adevelop'})

# # Extract the number from the element's text
# closed_count = int(closed_count_element.text.strip())

# # Print the result
# print(f"Number of closed pull requests: {closed_count}")

'''Dealing with non-closed pull requests'''
# import requests
# from bs4 import BeautifulSoup

# url = 'https://github.com/trilinos/Trilinos/pulls?q=is%3Apr+merged%3A2023-02-21T12%3A00%3A00-07%3A00..2023-02-22T12%3A00%3A00-07%3A00+base%3Adevelop+'

# # Send a GET request to the URL
# response = requests.get(url)

# # Create a BeautifulSoup object to parse the HTML content
# soup = BeautifulSoup(response.content, 'html.parser')

# # Find the element containing the number of closed pull requests
# closed_count_element = soup.find('a', {'href': '?q=is%3Apr+is%3Aclosed+merged%3A2023-02-21T12%3A00%3A00-07%3A00..2023-02-22T12%3A00%3A00-07%3A00+base%3Adevelop'})

# # Check if the element was found and extract the number from its text
# if closed_count_element is not None:
#     closed_count = int(closed_count_element.text.strip())
#     print(f"Number of closed pull requests: {closed_count}")
# else:
#     print("Error: Could not find closed count element.")

'''


To use the GitHub API to find all the closed pull requests on a provided repository using Python, you can use the requests module to make HTTP requests to the GitHub API and the json module to parse the response.

Before you begin, you will need to have a GitHub account and generate a personal access token with the "repo" scope. You can do this by going to "Settings" -> "Developer settings" -> "Personal access tokens" and creating a new token.

Here's a Python script that uses the GitHub API to find all the closed pull requests on a provided repo:




'''
import requests
import json

# replace these values with your own
repo_owner = "owner"
repo_name = "repo"
access_token = "your_access_token"

# construct the API endpoint URL
url = f"https://api.github.com/repos/{repo_owner}/{repo_name}/pulls"

# set the query parameters to filter only closed pull requests
params = {"state": "closed"}

# add the access token to the headers for authentication
headers = {"Authorization": f"token {access_token}"}

# make the API request and parse the response
response = requests.get(url, headers=headers, params=params)
data = json.loads(response.content)

# loop through the pull requests and print their numbers and titles
for pr in data:
    print(f"#{pr['number']} - {pr['title']}")

'''





'''