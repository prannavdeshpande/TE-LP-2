import streamlit as st
import nltk

nltk.download('punkt', quiet=True)
nltk.download('averaged_perceptron_tagger', quiet=True)
nltk.download('wordnet', quiet=True)

from nltk.stem import WordNetLemmatizer
from nltk.tokenize import word_tokenize
from nltk.chat.util import Chat,reflections


pairs = [
    [r".*\bmy name is (.*)", ["Hello %1, welcome to MovieBot!"]],
    [r".*\b(hi|hello|hey)\b.*", ["Hi there! How can I help you with your tickets?"]],
    [r"how are you?", ["I’m just code, but always ready to book your movie!"]],
    [r"\bbook\b(.*)\btickets\b(.*)", ["Sure! Booking %1 tickets for %2. Please confirm the date and time."]],
    [r".*\bbook\b.*\bticket[s]?\b.*", ["Sure! Tell me the movie and number of tickets."]],
    [r".*\bcancel\b.*\bticket[s]?\b.*", ["I can help you cancel. What's your booking ID?"]],
    [r".*\b(movie[s]?|show[s]?)\b.*\b(playing|available)\b.*", ["Movies currently playing:\n- Dune\n- Batman\n- Avatar"]],
    [r".*\b(show|timing[s]?)\b.*\b(for)\b (.+)", ["Show timings for %1:\n- 10:30 AM\n- 1:30 PM\n- 4:45 PM\n- 8:00 PM"]],  # Use handler function
    [r".*\b(thank you|thanks)\b.*", ["You're welcome!"]],
    [r".*\b(quit|exit)\b.*", ["Goodbye! Enjoy your movie!"]],
    [r"(.*)", ["Sorry, I didn't understand that. Can you rephrase?"]]
]


class RuleBasedChatbot:
    def __init__(self,pairs):
        self.chatbot = Chat(pairs,reflections)
    
    def preprocess(self,input):
        lemmatizer = WordNetLemmatizer()
        tokenized_words = word_tokenize(input)
        filtered_words = [lemmatizer.lemmatize(x) for x in tokenized_words]
        return " ".join(filtered_words)

    def response(self,input):
        preprocessed_input = self.preprocess(input)
        return self.chatbot.respond(preprocessed_input)

st.title("Chatbot")
st.write("chat with me : )")

if 'chatbot' not in st.session_state:
    st.session_state.chatbot = RuleBasedChatbot(pairs)

if 'history' not in st.session_state:
    st.session_state.history = []

def handle_input():
    if st.session_state.user_input:
        userInput = st.session_state.user_input
        response = st.session_state.chatbot.response(userInput)
        st.session_state.history.append(("You",userInput))
        st.session_state.history.append(("Bot",response))
        st.session_state.user_input = ""

st_container = st.container()

with st_container:
    for sender,msg in st.session_state.history:
        if sender == "You":
            st.markdown(f"<div style='text-align: right; background-color: #ffffff; padding: 10px; border-radius: 10px; margin: 5px 0;color:black;'><b>{sender}:</b> {msg}</div>", unsafe_allow_html=True)
        else:
            st.markdown(f"<div style='background-color: #bcff70; padding: 10px; border-radius: 10px; margin: 5px 0;color:black;'><b>{sender}:</b> {msg}</div>", unsafe_allow_html=True)

st.text_input("You:",key="user_input",on_change = handle_input)

# streamlit run app.py
