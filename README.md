
# Cloud Natural Language API (C++)
C++ implmentations using Google's Nautral Language API. Checkout Google's [Natual Language API](https://cloud.google.com/natural-language/)
ALL projects  use  gRPC wich you can checkout at their [Main Website](http://www.grpc.io/) or the [Git Repo](https://github.com/grpc/grpc)

## Overview

gRPC implimentations of Google's "Cloud Natural Language API" in C++.
https://cloud.google.com/natural-language/docs/reference/rpc/


## Usage

### Prerequisites
To use this you need to install and configure the [Google Cloud SDK](https://cloud.google.com/sdk/).

``` Arch linux: 

yaourt -S google-cloud-sdk
```

Install and configure [Protocol Buffers (proto3)](https://developers.google.com/protocol-buffers/) along with gRPC. The [Quickstart](http://www.grpc.io/docs/quickstart/cpp.html) section on grpc.io covers the installation/setup process in more detail. 

```Arch Linux:
Note: This installs both gRPC and Proto3.

yaourt -S grpc
```

### Tweak the code
There are section of the code you will need to change before using. These sections should be marked with a comment "TODO". Read the comment on that line and it's corrosponding TODO comment found on the bottom of the page.


### Compile
In order to compile this you will need to use *make*.

### Running
```
./natural_language
```

*REQUEST*

_AnalyzeEntities_: "Entity Analysis inspects the given text for known entities (proper nouns such as public figures, landmarks, etc.), and returns information about those entities. Entity analysis is performed with the analyzeEntities method." [Source](https://cloud.google.com/natural-language/docs/analyzing-entities)
    
_AnalizeSentiment_:  "Sentiment Analysis inspects the given text and identifies the prevailing emotional opinion within the text, especially to determine a writer's attitude as positive, negative, or neutral. Sentiment analysis is performed through the analyzeSentiment method. Currently English, Spanish, and Japanese languages are supported for sentiment analysis." [Source](https://cloud.google.com/natural-language/docs/analyzing-sentiment)
    
_AnalyzeSyntax_: "Syntactic Analysis extracts linguistic information, breaking up the given text into a series of sentences and tokens (generally, word boundaries), providing further analysis on those tokens. Syntactic Analysis is performed with the analayzeSyntax method." [Source](https://cloud.google.com/natural-language/docs/analyzing-syntax)
    
_AnnotateText_: "The request message for the text annotation API, which can perform multiple analysis types (sentiment, entities, and syntax) in one call." [Source](https://cloud.google.com/natural-language/docs/reference/rpc/google.cloud.language.v1#google.cloud.language.v1.AnnotateTextRequest)
    
*CONTENT*

*: This can be a word, sentence, maybe paragraph. I've only tested a sentence or two and haven't looked into what the charter limit is.
    

## Please Note

04/05/2017 - Google's [documentation](https://cloud.google.com/natural-language/docs/reference/rpc/google.cloud.language.v1#google.cloud.language.v1.PartOfSpeech.Case) has a message "PartOfSpeech.Case" while this is valid the variable, "case" is not. This has been changed in the protofile to "instance".



