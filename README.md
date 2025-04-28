CS5293-002_Project3

Chloe Moore

Instructions on how to run code are in howtorun.txt file


Functional Description:

This C++ search engine is built with a modular architecture to efficiently process and search through a collection of documents. The system is composed of several key modules: the DocumentParser reads documents, extracts important terms, cleans and stems text, and passes the processed terms to the IndexHandler. The IndexHandler stores these terms in a self-balancing AVL tree, allowing for fast insertion and retrieval. When a user submits a query through the UserInterface, it is forwarded to the SearchEngine, which coordinates the search process by passing the query to the QueryProcessor. The QueryProcessor parses the query, retrieves matching documents by searching the index, ranks the results based on relevance, and returns them for display. The SearchEngine manages the entire flow between parsing, indexing, and querying, while the UserInterface captures user input and presents search results clearly. The dataset used for this project is stored in the Data/ directory, where documents are parsed and indexed during the setup phase. Testing modules such as documentparsertest.cpp, indexhandlertest.cpp, and queryprocessortest.cpp verify the functionality and reliability of each major component.


Design Description:

The search engine is designed around a modular, component-driven architecture to ensure scalability, maintainability, and efficiency. It follows a linear data flow where documents are first parsed, indexed, and then queried by users. The system begins with the DocumentParser, which is responsible for reading raw documents, cleaning and normalizing their contents, and extracting stemmed terms for indexing. These terms are then stored in a balanced AVL tree within the IndexHandler, enabling rapid term lookup and efficient memory management. To handle user interactions, the UserInterface collects queries and displays results in a straightforward format. Behind the scenes, the SearchEngine acts as the central coordinator, managing document ingestion, index construction, and query execution. When a user submits a search request, the SearchEngine passes it to the QueryProcessor, which interprets the query, searches the AVL-based index for matching terms, ranks the results based on relevance, and sends them back for display. All components interact cleanly through well-defined interfaces, promoting separation of concerns and ease of debugging. The dataset for the engine is housed in a dedicated Data/ directory, serving as the input for indexing and search operations. Overall, the design emphasizes speed, modularity, and clarity, ensuring that each module has a focused, independent role while contributing to a cohesive, efficient search experience.


Resources: chatgpt.com, json.org, rapidjson.org, wikipedia.org, Ria Mukherji, Anekah Kelley, Megan Appel, Diego Mejia
