package assignment_4;

// import necessary packages to use built-in classes as required
import java.util.Random;

class QuoteOfTheDay {
	public static void main (String[] args) {

		// 1d array to store the hard-coded strings
		String []quote = new String[] {
            "'You have to write the book that wants to be written. And if the book will be too difficult for grown-ups, then you write it for children.'--Madeleine L'Engle",
            "'If you don't have time to read, you don't have the time (or the tools) to write. Simple as that.'--Stephen King",
            "'We write to taste life twice, in the moment and in retrospect.'--Anaïs Nin",
            "'Substitute 'damn' every time you're inclined to write 'very;' your editor will delete it and the writing will be just as it should be.'--Mark Twain",
            "'If there's a book that you want to read, but it hasn't been written yet, then you must write it.'--Toni Morrison",
            "'One day I will find the right words, and they will be simple.'--Jack Kerouac, The Dharma Bums",
            "'Either write something worth reading or do something worth writing.'--Benjamin Franklin",
            "'You never have to change anything you got up in the middle of the night to write.'--Saul Bellow",
            "'No tears in the writer, no tears in the reader. No surprise in the writer, no surprise in the reader.--Robert Frost",
            "'Read, read, read. Read everything -- trash, classics, good and bad, and see how they do it. Just like a carpenter who works as an apprentice and studies the master. Read! You'll absorb it. Then write. If it's good, you'll find out. If it's not, throw it out of the window.'--William Faulkner",
            "'You must stay drunk on writing so reality cannot destroy you.'--Ray Bradbury, Zen in the Art of Writing",
            "'Words can be like X-rays if you use them properly -- they'll go through anything. You read and you're pierced.'--Aldous Huxley, Brave New World",
            "'How vain it is to sit down to write when you have not stood up to live.'--Henry David Thoreau",
            "'I can shake off everything as I write; my sorrows disappear, my courage is reborn.'--Anne Frank",
            "'A writer is someone for whom writing is more difficult than it is for other people.'--Thomas Mann, Essays of Three Decades",
            "'Let me live, love, and say it well in good sentences.'--Sylvia Plath, The Unabridged Journals of Sylvia Plath",
            "'Here is a lesson in creative writing. First rule: Do not use semicolons. They are transvestite hermaphrodites representing absolutely nothing. All they do is show you've been to college.'--Kurt Vonnegut Jr., A Man Without a Country",
            "'Don't bend; don't water it down; don't try to make it logical; don't edit your own soul according to the fashion. Rather, follow your most intense obsessions mercilessly.'--Franz Kafka",
            "'I kept always two books in my pocket, one to read, one to write in.'--Robert Louis Stevenson",
            "'You can make anything by writing.'--C.S. Lewis",
            "'A word after a word after a word is power.'--Margaret Atwood",
            "'Tears are words that need to be written.'--Paulo Coelho",
            "'You should write because you love the shape of stories and sentences and the creation of different words on a page. Writing comes from reading, and reading is the finest teacher of how to write.'--Annie Proulx",
            "'To survive, you must tell stories.'--Umberto Eco, The Island of the Day Before",
            "'Always be a poet, even in prose.'--Charles Baudelaire",
            "'If my doctor told me I had only six minutes to live, I wouldn't brood. I'd type a little faster.'--Isaac Asimov",
            "'The purpose of a writer is to keep civilization from destroying itself.'--Albert Camus",
            "'I write to discover what I know.'--Flannery O'Connor",
            "'Ideas are like rabbits. You get a couple and learn how to handle them, and pretty soon you have a dozen.'― John Steinbeck",
            "'Words do not express thoughts very well. They always become a little different immediately after they are expressed, a little distorted, a little foolish.'― Hermann Hesse",
            "'When you make music or write or create, it's really your job to have mind-blowing, irresponsible, condomless sex with whatever idea it is you're writing about at the time.'--Lady Gaga" 
        };

        Random rand = new Random ();
        int i = rand.nextInt (quote.length);	// generate a random index in the range 0 to length-1 inclusive
        System.out.println (quote[i]);
	}
}