#!/usr/bin/python3
import os
import zipfile

def build( zipFilename: str, name: str ):
	def zipdir( name, path, ziph ):
		for root, dirs, files in os.walk( path ):
			print( "root: {}\ndirs: {}\nfiles: {}".format( root, dirs, files ) )
			for filename in files:
				print( "filername: {}".format( filename ) )
				ziph.write( os.path.join( root, filename ), 
							os.path.join( name, root, filename ) ) 

		return
	
	zipf = zipfile.ZipFile( zipFilename, 'w', zipfile.ZIP_DEFLATED )
	for filename in ( 'keywords.txt', 'library.properties', 'LICENSE', 'README.md', 'CHANGES.md'  ):
		zipf.write( os.path.join( filename ),
					os.path.join( name, filename ) ) 

	zipdir( name, 'src/', zipf )
	zipdir( name, 'extras/', zipf )
	zipdir( name, 'examples/', zipf )
	zipf.close()
	return

def main():
	build( os.path.join( 'build', 'cli.zip' ), 'CommandLineIntf' )
	return

if __name__ == '__main__':
	main()

