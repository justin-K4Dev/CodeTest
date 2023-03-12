# List Comprehensions

# List Comprehensions is a very powerful tool, which creates a new list based on another list, in a single, readable line.

# For example, let's say we need to create a list of integers which specify the length of each word in a certain sentence,
# but only if the word is not the word "the".

sentence = "the quick brown fox jumps over the lazy dog"
words = sentence.split()
print( worlds )
#output: ['the', 'quick', 'brown', 'fox', 'jumps', 'over', 'the', 'lazy', 'dog']
 
word_lengths = []
for word in words:
    if word != "the":
        word_lengths.append(len(word))
print( word_lengths )
#output: [5, 5, 3, 5, 4, 4, 3]

# Using a list comprehension, we could simplify this process to this notation:

sentence = "the quick brown fox jumps over the lazy dog"
words = sentence.split()
#output: ['the', 'quick', 'brown', 'fox', 'jumps', 'over', 'the', 'lazy', 'dog']

print( words )
word_lengths = [len(word) for word in words if word != "the"]
print( word_lengths )
#output: [5, 5, 3, 5, 4, 4, 3]