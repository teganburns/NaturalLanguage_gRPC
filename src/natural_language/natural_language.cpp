// Author: Tegan Burns
// Website: teganburns.com

#include "natural_language.hpp.in"

// -------------------- //

AnalyzeEntitiesRequest MakeAnalyzeEntitiesRequest( Document_Type doc_type_, std::string doc_language_, std::string doc_content_ ) {

    AnalyzeEntitiesRequest request_;
    MakeDocument( doc_type_, doc_language_, doc_content_ );
    MakeEncodingType( );
	return request_;

}

AnalyzeSentimentRequest MakeAnalyzeSentimentRequest( Document_Type doc_type_, std::string doc_language_, std::string doc_content_ ) {

    AnalyzeSentimentRequest request_;
	return request_;
}


AnalyzeSyntaxRequest MakeAnalyzeSyntaxRequest( Document_Type doc_type_, std::string doc_language_, std::string doc_content_ ) {

    AnalyzeSyntaxRequest request_;
	return request_;
}


AnnotateTextRequest MakeAnnotateTextRequest( Document_Type doc_type_, std::string doc_language_, std::string doc_content_ ) {

	AnnotateTextRequest request_;
	return request_;
}

DependencyEdge MakeDependencyEdge( ) {

	DependencyEdge dependencyedge_;
	return dependencyedge_;

}

Document MakeDocument( Document_Type type_, std::string language_, std::string content_ ) {

	Document document_;

	document_.set_type( type_ );
	// TODO: Not sure how to to go about this. Pretty sure there's only supposed to be one of these...?
	// document_.mutable_
	return document_;

}

EncodingType MakeEncodingType( ) {

	EncodingType encodingtype_;
	return encodingtype_;
}


Entity MakeEntity( ) {

	Entity entity_;
	return entity_;    
}

EntityMention MakeEntityMention( ) {

	EntityMention entitymention_;
	return entitymention_;
}

PartOfSpeech MakePartOfSpeech( ) {

	PartOfSpeech partofspeech_;
	return partofspeech_;
    
}

Sentence MakeSentence( ) {

	Sentence sentence_;
	return sentence_;
	
}

Sentiment MakeSentiment( ) {

	Sentiment sentiment_;
	return sentiment_;    
}

TextSpan MakeTextSpan( std::string content_, long begin_offset_ ) {

    TextSpan textspan_;
    textspan_.set_content( content_ );
	return textspan_;
}

Token MakeToken( std::string content_, long begin_offset_ ) {

    Token token_;
    token_.mutable_text()->CopyFrom( MakeTextSpan( content_, begin_offset_ ) );
    token_.mutable_part_of_speech()->CopyFrom( MakePartOfSpeech( ) );
    token_.mutable_dependency_edge()->CopyFrom( MakeDependencyEdge( ) );

    return token_;
    
}


// -------------------- //



bool  set_document( Document* doc ) {

    int content_type;
    std::string content, content_file;
    std::fstream file;
    char content_c[256];
    std::string name;
    std::stringstream content_buffer;

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
            content_buffer << file.rdbuf();
            file.close();
            doc->set_content( content_buffer.str() );
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
            std::exit( EXIT_FAILURE );
            break;
    
    } 


    std::cout << "\nAll Finished!" << std::endl;
    //::google::protobuf::ShutdownProtobufLibrary();
    return 0;

}

// TODO: [METADATA_MAP] Finish reading this back. //
//
