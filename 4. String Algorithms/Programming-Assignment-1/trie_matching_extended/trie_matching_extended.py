# python3
import sys

def build_trie(patterns):
  tree = { 0: { } }
  tree_index = 0
  for pattern in patterns:
    current_node = tree[0]
    for letter in pattern:
      if letter in current_node:
        current_node = tree[current_node[letter]]
      else:
        tree_index += 1
        tree[tree_index] = {}
        current_node[letter] = tree_index
        current_node = tree[tree_index]
    current_node["leaf"] = True
  return tree

def prefix_trie_matching(text, trie):
  text += "$"
  symbol_index = 0
  v = trie[0]
  symbol = text[0]
  while True:
    if "leaf" in v:
      return True
    elif symbol in v:
      v = trie[v[symbol]]
      symbol_index += 1
      symbol = text[symbol_index]
    else:
      return False

def solve (text, n, patterns):
  result = []

  trie = build_trie(patterns)
  for index in range(len(text)):
    if prefix_trie_matching(text[index:], trie):
      result.append(index)

  return result

text = sys.stdin.readline ().strip ()
n = int (sys.stdin.readline ().strip ())
patterns = []
for i in range (n):
  patterns += [sys.stdin.readline ().strip ()]

ans = solve (text, n, patterns)

sys.stdout.write (' '.join (map (str, ans)) + '\n')