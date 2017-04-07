// Author: Tegan Burns-Berger
#include <iostream>
#include <unistd.h>
#include <fstream>

#include <grpc++/grpc++.h>
#include "NaturalLanguage.grpc.pb.h"

//using namespace std;
using namespace google::cloud::language::v1;


using grpc::CompletionQueue;
using grpc::Channel;
using grpc::RpcService;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;

using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

std::string SCOPE = "language.googleapis.com";


int AnalyzeEntities();
int AnalyzeSentiment();
int AnalyzeSyntax();
int AnnotateText();
bool set_document( Document* doc);


int AnalyzeEntities () {


    std::cout << "\n\n------AnalyzeEntities------" << std::endl;

    // Init Objects //
    
    // Document //
    
    // EncodingType // 


    return 0;

}

int AnalyzeSentiment () {


    std::cout << "\n\n------AnalyzeSentiment------" << std::endl;

    // Init Objects //
    
    // Document //
    
    // EncodingType // 
    

    return 0;

}

int AnalyzeSyntax () {

    //----------------------//
    // AnnotateText Request //
    //----------------------//

    std::cout << "\n\n------AnalyzeSyntax------" << std::endl;

    // Init Objects //
    
    // Document //
    
    // EncodingType // 


    return 0;
}

int AnnotateText () {

    //----------------------//
    // AnnotateText Request //
    //----------------------//

    std::cout << "\n\n------AnnotateText------" << std::endl;

    // Init Objects //
    std::cout << "Init Objects...";
    AnnotateTextRequest request;
    Document *document;
    AnnotateTextRequest_Features *features;
    EncodingType encoding_type;
    AnnotateTextResponse response;
    grpc::Status status;
    grpc::ClientContext context;
    std::cout << "Done!" << std::endl;

    sleep(0.5);

    // Document //
    set_document( request.mutable_document() );

    sleep(0.5);
     
    // Features //
    std::cout << "Setting Features...";
    features = request.mutable_features();
    features->set_extract_syntax( 1 );
    features->set_extract_entities( 1 );
    features->set_extract_document_sentiment( 1 );
    std::cout << "Done!" << std::endl;

    sleep(0.5);

    // EncodingType //
    std::cout << "Setting Encoding...";
    request.set_encoding_type( EncodingType::UTF8 );
    std::cout << "Done!" << std::endl;

    sleep(0.5);


    // Send Request //
    auto creds = grpc::GoogleDefaultCredentials();
    auto channel = grpc::CreateChannel( SCOPE, creds );
    std::unique_ptr< LanguageService::Stub> stub( LanguageService::NewStub( channel ) );
    status = stub->AnnotateText( &context, request, &response );

    // AnnotateText Response //
    std::cout << "status.ok(): " << status.ok() << std::endl;

    if ( status.ok() ) {
        std::cout << "\n\n------Response------" << std::endl << std::endl;
        std::cout << "Status returned OK" << std::endl;


        // SENTENCES //
        std::cout << "----Sentences----" << std::endl;
        std::cout << "Sentences Size: " << response.sentences_size() << std::endl;
        for( int i = 0; i < response.sentences_size(); i++ ) {
            std::cout << "Sentence " << i << " has text: " << response.sentences( i ).has_text() << std::endl;
            if ( response.sentences( i ).has_text() ) {
                std::cout << "\tSentence text: " << response.sentences( i ).text().content() << std::endl;
            }

            std::cout << "Sentence " << i << " has sentiment: " << response.sentences( i ).has_sentiment() << std::endl;
            if ( response.sentences( i ).has_text() ) {
                std::cout << "\tSentence " << i << " sentiment: "
                    << "\n\t\tMagnitude: "
                    << response.sentences( i ).sentiment().magnitude() // float
                    << "\n\t\tScore: "
                    << response.sentences( i ).sentiment().score() // float
                    << std::endl;
            }

        }

        // TOKENS //
        std::cout << "\n----Tokens----" << std::endl;
        std::cout << "Tokens Size: " << response.tokens_size() << std::endl;
        for ( int i = 0; i < response.tokens_size(); i++ ) {
           
            std::cout
                << "-- Token " << i << " --"
                << std::endl;

            std::cout
                << "Token " << i << " has text: " 
                << response.tokens( i ).has_text() 
                << std::endl;

            if ( response.tokens( i ).has_text() ) {
                std::cout
                    << "\tToken " << i << " text: " 
                    << response.tokens( i ).text().content() // string
                    << "\n\tScore: "
                    << response.tokens( i ).text().begin_offset() // int32 
                    << std::endl;
            }

            std::cout
                << "Token " << i << " has PartOfSpeech: " 
                << response.tokens( i ).has_part_of_speech() 
                << std::endl;

            if ( response.tokens( i ).has_part_of_speech() ) {
                std::cout
                    << "\tToken " << i << " PartOfSpeech: "
                    << "\n\t\tAspect: "
                    << PartOfSpeech_Aspect_Name( response.tokens( i ).part_of_speech().aspect() )
                    << "\n\t\tCase: "
                    << PartOfSpeech_Case_Name( response.tokens( i ).part_of_speech().instance() )
                    << "\n\t\tForm: "
                    << PartOfSpeech_Form_Name( response.tokens( i ).part_of_speech().form() )
                    << "\n\t\tGender: "
                    << PartOfSpeech_Gender_Name( response.tokens( i ).part_of_speech().gender() )
                    << "\n\t\tMood: "
                    << PartOfSpeech_Mood_Name( response.tokens( i ).part_of_speech().mood() )
                    << "\n\t\tNumber: "
                    << PartOfSpeech_Number_Name( response.tokens( i ).part_of_speech().number() )
                    << "\n\t\tPerson: "
                    << PartOfSpeech_Person_Name( response.tokens( i ).part_of_speech().person() )
                    << "\n\t\tProper: "
                    << PartOfSpeech_Proper_Name( response.tokens( i ).part_of_speech().proper() )
                    << "\n\t\tReciprocity: "
                    << PartOfSpeech_Reciprocity_Name( response.tokens( i ).part_of_speech().reciprocity() )
                    << "\n\t\tTag: "
                    << PartOfSpeech_Tag_Name( response.tokens( i ).part_of_speech().tag() )
                    << "\n\t\tTense: "
                    << PartOfSpeech_Tense_Name( response.tokens( i ).part_of_speech().tense() )
                    << "\n\t\tVoice: "
                    << PartOfSpeech_Voice_Name( response.tokens( i ).part_of_speech().voice() )


                    << std::endl;
            
            }
        
            std::cout
                << "Token " << i << " has DependencyEdge: "
                << response.tokens( i ).has_dependency_edge()
                << std::endl;

            if ( response.tokens( i ).has_dependency_edge() ) {
                std::cout
                    << "\tToken " << i << " DependencyEdge: "
                    << "\n\t\tHead Token Index: "
                    << response.tokens( i ).dependency_edge().head_token_index() // int32
                    << "\n\t\tLabel: "
                    << DependencyEdge_Label_Name( response.tokens( i ).dependency_edge().label() )
                    << std::endl;
            
            }

            std::cout
                << "Token " << i << " lemma: "
                << response.tokens( i ).lemma() // string
                << std::endl
                << std::endl;

        }

        // ENTITIES //
        std::cout << "\n----Entities----" << std::endl;
        std::cout << "Entities Size: " << response.entities_size() << std::endl;
        for ( int i = 0; i < response.entities_size(); i++ ) {
            std::cout << "Entity " << i << " name: " << response.entities( i ).name() << std::endl;
            
            std::cout
                << "Entity Type: "
                << Entity_Type_Name( response.entities( i ).type() )
                << std::endl;

            for ( int j = 0; j < response.entities( i ).metadata_size(); j++ ) {
                //response.entities( i ).metadata( j ) // ::google::protobuf::Map
            }
            
            std::cout
                << "Salience: "
                << response.entities( i ).salience() // float
                << std::endl;

            for ( int j = 0; j < response.entities( i ).mentions_size(); j++ ) {
                
                std::cout
                    << "Entity Mention " << j << " has text: "
                    << response.entities( i ).mentions( j ).has_text()
                    << std::endl;

                if ( response.entities( i ).mentions( j ).has_text() ) {
                    std::cout
                        << "\tEntity Mention " << j << " text content: "
                        << response.entities( i ).mentions( j ).text().content()
                        << "\n\tEntity Mention " << j << " text begin offset: "
                        << response.entities( i ).mentions( j ).text().begin_offset()
                        << "\n\tEntity Mention " << j << " type: "
                        << EntityMention_Type_Name( response.entities( i ).mentions( j ).type() )
                        << std::endl;
                }
            }


        }


        // SENTIMENT /
        std::cout << "\n----Sentiment----" << std::endl;
        std::cout << "Has Document Sentiment: " << response.has_document_sentiment() << std::endl;
        
        if ( response.has_document_sentiment() ) {
            std::cout
                << "Document Sentiment magnitude: "
                << response.document_sentiment().magnitude()
                << "\nDocument Sentiment score: "
                << response.document_sentiment().magnitude()
                << std::endl;
        }

        // LANGUAGE //
        std::cout << "\n----Language----" << std::endl;
        std::cout << "Language: " << response.language() << std::endl;


    } else if ( status.ok() ){
        std::cout << "Status Returned Canceled" << std::endl;

    }else {
        std::cout << "gRPC Status Error Code: " << status.error_code() << "\ngRPC Status Error Message: " << status.error_message() << std::endl;
        std::cerr << "RPC failed" << std::endl;;
        return -1;
    }

    std::cout << "\nAll Finished!" << std::endl;





    return 0;

}

// Document.type() //
// Document.set_content() //
// Document.set_gcs_content_uri() //
bool  set_document( Document* doc ) {

    int content_type;
    std::string content, content_file;
    std::fstream file;
    char content_c[256];
    std::string name;

    system("clear");

    std::cout
        << "---- Content Type ---- "
        << "\n\t[1] Local content (file)"
        << "\n\t[2] Local content (key input)"
        << "\n\t[3] GCS URL (Google Cloud Storage URL)"
        << "\nPlease select a number...";

    std::cin >> content_type;

    switch ( content_type ) {
        case 1:
            // Get string input of file path //
            doc->set_type( Document_Type::Document_Type_PLAIN_TEXT );
            std::cout << "Please enter the file to be analyzed: ";
            std::cin >> content_file;
            file.open( content_file, std::ios::in);
            file.close();
            doc->set_content( content );
            break;
        case 2:
            // Local Content //
            doc->set_type( Document_Type::Document_Type_PLAIN_TEXT );
            std::cout << "\nPlease enter the text to be analyzed: ";
            std::cin.ignore( 1 , '\n');
            std::getline(std::cin, content, '\n' );
            std::cout << "\nYou typed: " << content << std::endl;
            doc->set_content( content );
            break;
        case 3:
            // gcs uri //
            doc->set_type( Document_Type::Document_Type_HTML ); 
            std::cout << "\nPlease enter the gcs content uri: ";
            std::cin >> content;
            doc->set_gcs_content_uri( content );
            break;
        default:
            std::cerr << "Selection \"" << content_type << "\" is not valid." << std::endl;
            return false;
            break;
    
    }

    return true;
}

int main ( int argc, char* argv[] ) {

    system("clear");
    GOOGLE_PROTOBUF_VERIFY_VERSION;
 
    int request_type;

    std::cout
        << "---- Request Type ----"
        << "\n\t[1] AnalyzeEntities"
        << "\n\t[2] AnalyzeSentiment"
        << "\n\t[3] AnalyzeSyntax"
        << "\n\t[4] AnnotateText"
        << "\nPlease select a number...";

    std::cin >> request_type;
    system("clear");

    switch ( request_type ) {
        case 1:
            AnalyzeEntities();
            break;
        case 2:
            AnalyzeSentiment();
            break;
        case 3:
            AnalyzeSyntax();
            break;
        case 4:
            AnnotateText();
            break;
        default:
            std::cout << "Selection \"" << request_type << "\" is not valid." << std::endl;
            break;
    
    } 


    //::google::protobuf::ShutdownProtobufLibrary();
    return 0;

}

// TODO: In AnnotateText(), document->set_source() currently only accepts "gs://" content, even when document->set_type() is set to PLAIN_TEXT. //
//
//
//
